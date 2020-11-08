// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2018 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_PRIMITIVES_BLOCK_H
#define BITCOIN_PRIMITIVES_BLOCK_H

#include <primitives/transaction.h>
#include <serialize.h>
#include <uint256.h>

/** Nodes collect new transactions into a block, hash them into a hash tree,
 * and scan through nonce values to make the block's hash satisfy proof-of-work
 * requirements.  When they solve the proof-of-work, they broadcast the block
 * to everyone and the block is added to the block chain.  The first transaction
 * in the block is a special one that creates a new coin owned by the creator
 * of the block.
 */
class CBlockHeader
{
public:
    // header
    int32_t nVersion;
    uint256 hashPrevBlock;
    uint256 hashMerkleRoot;
    uint32_t nTime;
    uint32_t nBits;
    uint32_t nNonce;
    uint32_t nFlags;
    
    bool fProofOfBurn;
    uint256 hashBurnBlock;
  	uint256 burnHash;
    uint32_t burnBlkHeight;
    uint32_t burnCTx;
    uint32_t burnCTxOut;
    uint64_t nEffectiveBurnCoins;
  	uint32_t nBurnBits;
    
    std::vector<CTransactionRef> vtx;
    std::vector<unsigned char> vchBlockSig;
	mutable std::vector<uint256> vMerkleTree;
	
	mutable int nDoS;
  	bool DoS(int nDoSIn, bool fIn) const { nDoS += nDoSIn; return fIn; }
  
    // slimcoin: Used in CheckProofOfStake().
    static const int32_t NORMAL_SERIALIZE_SIZE=80;
    static const int32_t CURRENT_VERSION=1;

    CBlockHeader()
    {
        SetNull();
    }

    ADD_SERIALIZE_METHODS;

    template <typename Stream, typename Operation>
    inline void SerializationOp(Stream& s, Operation ser_action) {
        READWRITE(this->nVersion);
        nVersion = this->nVersion;
        READWRITE(hashPrevBlock);
        READWRITE(hashMerkleRoot);
        READWRITE(nTime);
        READWRITE(nBits);
        READWRITE(nNonce);
        
        READWRITE(fProofOfBurn);
        READWRITE(hashBurnBlock);
        READWRITE(burnHash);
        READWRITE(burnBlkHeight);
        READWRITE(burnCTx);
        READWRITE(burnCTxOut);
        READWRITE(nEffectiveBurnCoins);
        READWRITE(nBurnBits);

        if (!(s.GetType() & SER_GETHASH) && s.GetType() & SER_POSMARKER)
      	{
        	READWRITE(vtx);
        	READWRITE(vchBlockSig);
        	
      	} 
    }

    void SetNull()
    {
        nVersion = CURRENT_VERSION;
        hashPrevBlock.SetNull();
        hashMerkleRoot.SetNull();
        nTime = 0;
        nBits = 0;
        nNonce = 0;
        
        fProofOfBurn = false;
        hashBurnBlock.SetNull();
    	burnHash.SetNull();
    	burnBlkHeight = burnCTx = burnCTxOut = -1; //set indexes to negative
    	nEffectiveBurnCoins = 0;
    	nBurnBits = 0;

    	vtx.clear();
    	vchBlockSig.clear();
    	vMerkleTree.clear();
    	nDoS = 0;
    
    }

    bool IsNull() const
    {
        return (nBits == 0);
    }

    uint256 GetHash() const;

    int64_t GetBlockTime() const
    {
        return (int64_t)nTime;
    }
};


class CBlock : public CBlockHeader
{
public:
    // network and disk
    std::vector<CTransactionRef> vtx;

    // slimcoin: block signature - signed by coin base txout[0]'s owner
    std::vector<unsigned char> vchBlockSig;

    // memory only
    mutable bool fChecked;

    CBlock()
    {
        SetNull();
    }

    CBlock(const CBlockHeader &header)
    {
        SetNull();
        *(static_cast<CBlockHeader*>(this)) = header;
    }

    ADD_SERIALIZE_METHODS;

    template <typename Stream, typename Operation>
    inline void SerializationOp(Stream& s, Operation ser_action) {
        READWRITEAS(CBlockHeader, *this);
        READWRITE(vtx);
        READWRITE(vchBlockSig);
    }

    void SetNull()
    {
        CBlockHeader::SetNull();
        vtx.clear();
        fChecked = false;
        vchBlockSig.clear();
    }

    CBlockHeader GetBlockHeader() const
    {
        CBlockHeader block;
        block.nVersion       = nVersion;
        block.hashPrevBlock  = hashPrevBlock;
        block.hashMerkleRoot = hashMerkleRoot;
        block.nTime          = nTime;
        block.nBits          = nBits;
        block.nNonce         = nNonce;
        return block;
    }

    // slimcoin: two types of block: proof-of-work or proof-of-stake
    bool IsProofOfStake() const
    {
        return (vtx.size() > 1 && vtx[1]->IsCoinStake());
    }

    bool IsProofOfWork() const
    {
        return !IsProofOfStake();
    }

    std::pair<COutPoint, unsigned int> GetProofOfStake() const
    {
        return IsProofOfStake() ? std::make_pair(vtx[1]->vin[0].prevout, vtx[1]->nTime) : std::make_pair(COutPoint(), (unsigned int)0);
    }

    // slimcoin: get max transaction timestamp
    int64_t GetMaxTransactionTime() const
    {
        int64_t maxTransactionTime = 0;
        for (const auto& tx : vtx)
            maxTransactionTime = std::max(maxTransactionTime, (int64_t)tx->nTime);
        return maxTransactionTime;
    }

    unsigned int GetStakeEntropyBit() const; // slimcoin: entropy bit for stake modifier if chosen by modifier

    std::string ToString() const;
};

/** Describes a place in the block chain to another node such that if the
 * other node doesn't have the same branch, it can find a recent common trunk.
 * The further back it is, the further before the fork it may be.
 */
struct CBlockLocator
{
    std::vector<uint256> vHave;

    CBlockLocator() {}

    explicit CBlockLocator(const std::vector<uint256>& vHaveIn) : vHave(vHaveIn) {}

    ADD_SERIALIZE_METHODS;

    template <typename Stream, typename Operation>
    inline void SerializationOp(Stream& s, Operation ser_action) {
        int nVersion = s.GetVersion();
        if (!(s.GetType() & SER_GETHASH))
            READWRITE(nVersion);
        READWRITE(vHave);
    }

    void SetNull()
    {
        vHave.clear();
    }

    bool IsNull() const
    {
        return vHave.empty();
    }
};

#endif // BITCOIN_PRIMITIVES_BLOCK_H
