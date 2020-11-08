// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2019 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <chainparams.h>

#include <chainparamsseeds.h>
#include <consensus/merkle.h>
#include <tinyformat.h>
#include <util/system.h>
#include <util/strencodings.h>

#include <assert.h>

#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>

static CBlock CreateGenesisBlock(const char* pszTimestamp, const CScript& genesisOutputScript, uint32_t nTimeTx, uint32_t nTimeBlock, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    CMutableTransaction txNew;
    txNew.nVersion = 1;
    txNew.vin.resize(1);
    txNew.vout.resize(1);
    txNew.vin[0].scriptSig = CScript() << 486604799  << CScriptNum(9999) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
    txNew.vout[0].nValue = genesisReward;
    txNew.vout[0].scriptPubKey = genesisOutputScript;
    txNew.nTime = nTimeTx;

    CBlock genesis;
    genesis.nTime    = nTimeBlock;
    genesis.nBits    = nBits;
    genesis.nNonce   = nNonce;
    genesis.nVersion = nVersion;
    genesis.vtx.push_back(MakeTransactionRef(std::move(txNew)));
    //genesis.hashPrevBlock.SetNull();
    genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
    return genesis;
}

static CBlock CreateGenesisBlock(uint32_t nTimeTx, uint32_t nTimeBlock, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    const char* pszTimestamp = "RT: 2 southeast Ukranian regions to hold referendum May 11 as planned";
    const CScript genesisOutputScript = CScript();
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTimeTx, nTimeBlock, nNonce, nBits, nVersion, genesisReward);
}

/**
 * Main network
 */
class CMainParams : public CChainParams {
public:
    CMainParams() {
        strNetworkID = CBaseChainParams::MAIN;
        consensus.BIP34Height = 125;
        consensus.BIP34Hash = uint256S("00000766be5a4bb74c040b85a98d2ba2b433c5f4c673912b3331ea6f18d61bea");
        consensus.powLimit =            uint256S("00000000ffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.bnInitialHashTarget = uint256S("0000000000ffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        
        consensus.nTargetTimespan = 30 * 60;
        consensus.nStakeTargetSpacing = 90;
        consensus.nTargetSpacingWorkMax = 10 * consensus.nStakeTargetSpacing;
        consensus.nPowTargetSpacing = consensus.nStakeTargetSpacing;
        consensus.nStakeMinAge = 60 * 60 * 24 * 7;
        consensus.nStakeMaxAge = 60 * 60 * 24 * 90;
        consensus.nModifierInterval = 2 * 60 * 60;
        consensus.nCoinbaseMaturity = 500;

        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 1916;
        consensus.nMinerConfirmationWindow = 2016;
        
        consensus.nMinimumChainWork = uint256S("0x0");
        consensus.defaultAssumeValid = uint256S("0x0");
        
        pchMessageStart[0] = 0x6e;
        pchMessageStart[1] = 0x8b;
        pchMessageStart[2] = 0x92;
        pchMessageStart[3] = 0xa5;
        vAlertPubKey = ParseHex("04201f0f85178950503c20d5a947883dff81e727533f1f1da104755fa25275cf68c442b8ad50da3152c10a74ea621da614d3d2048ba25a14f39bfc40c41223543a");
        nDefaultPort = 9901;
        nPruneAfterHeight = 100000;
        m_assumed_blockchain_size = 313;
        m_assumed_chain_state_size = 0;

        genesis = CreateGenesisBlock(1399578460 , 1399578460, 116872, 0x1e0fffff, 1, 0 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        
        printf("hashGenesisBlock = %s\n", genesis.ToString().c_str());
        
        assert(genesis.hashMerkleRoot == uint256S("0xbae3867d5e5d35c321adaf9610b9e4147a855f9ad319fdcf70913083d783753f"));
        assert(consensus.hashGenesisBlock == uint256S("0x00000766be5a4bb74c040b85a98d2ba2b433c5f4c673912b3331ea6f18d61bea"));
        

        vSeeds.emplace_back("seed.slimcoin.bit");
        vSeeds.emplace_back("144.76.64.49");
        vSeeds.emplace_back("5.9.39.9");
        vSeeds.emplace_back("185.68.67.37");
        vSeeds.emplace_back("145.239.189.106");

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,63);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,125);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,183);
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x88, 0xB2, 0x1E};
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x88, 0xAD, 0xE4};

        bech32_hrp = "pc";

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));

        fMiningRequiresPeers = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = true;
        m_is_test_chain = true;
        m_is_mockable_chain = true;

        checkpointData = {
            {
                {     0, uint256S("0x00000766be5a4bb74c040b85a98d2ba2b433c5f4c673912b3331ea6f18d61bea")},
            }
        };

        chainTxData = ChainTxData{
            1591618067,
            1797921,
            0.00730216
        };
    }
};

/**
 * Testnet (v3)
 */
class CTestNetParams : public CChainParams {
public:
    CTestNetParams() {
        strNetworkID = CBaseChainParams::TESTNET;
        //consensus.BIP16Height = 0;
        consensus.BIP34Height = 293368;
        consensus.BIP34Hash = uint256S("00000002c0b976c7a5c9878f1cec63fb4d88d68d614aedeaf8158c42d904795e");
        consensus.powLimit =            uint256S("0000000fffffffffffffffffffffffffffffffffffffffffffffffffffffffff"); // ~arith_uint256(0) >> 28;
        consensus.bnInitialHashTarget = uint256S("00000007ffffffffffffffffffffffffffffffffffffffffffffffffffffffff"); // ~arith_uint256(0) >> 29;

        consensus.nTargetTimespan = 7 * 24 * 60 * 60;  // one week
        consensus.nStakeTargetSpacing = 10 * 60;  // 10-minute block spacing
        consensus.nTargetSpacingWorkMax = 12 * consensus.nStakeTargetSpacing; // 2-hour
        consensus.nPowTargetSpacing = consensus.nStakeTargetSpacing;
        consensus.nStakeMinAge = 60 * 60 * 24; // test net min age is 1 day
        consensus.nStakeMaxAge = 60 * 60 * 24 * 90;
        consensus.nModifierInterval = 60 * 20; // Modifier interval: time to elapse before new modifier is computed
        consensus.nCoinbaseMaturity = 60;

        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 1512; // 75% for testchains
        consensus.nMinerConfirmationWindow = 2016; // nPowTargetTimespan / nPowTargetSpacing
        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x00");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x0000000002e9e7b00e1f6dc5123a04aad68dd0f0968d8c7aa45f6640795c37b1"); //1135275

        pchMessageStart[0] = 0xcb;
        pchMessageStart[1] = 0xf2;
        pchMessageStart[2] = 0xc0;
        pchMessageStart[3] = 0xef;
        vAlertPubKey = ParseHex("04383862439513e940f6fcbf62d365c162a5256920c2c25b0b4266fdee4a443d71cfe224dbccff6fdb2ea57a37eb0cbec5637ebea06f63c70ca093672fbdc27643");
        nDefaultPort = 9903;
        nPruneAfterHeight = 1000;
        m_assumed_blockchain_size = 2;
        m_assumed_chain_state_size = 0;

        genesis = CreateGenesisBlock(1345083810, 1345090000, 122894938, 0x1d0fffff, 1, 0);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x00000001f757bb737f6596503e17cd17b0658ce630cc727c0cca81aec47c9f06"));
        assert(genesis.hashMerkleRoot == uint256S("0x3c2d8f85fab4d17aac558cc648a1a58acff0de6deb890c29985690052c5993c2"));

        vFixedSeeds.clear();
        vSeeds.clear();
        // nodes with support for servicebits filtering should be at the top
        vSeeds.emplace_back("tseed.slimcoin.net");
        vSeeds.emplace_back("tseed2.slimcoin.net");
        vSeeds.emplace_back("tseed.slimcoin-library.org");
        vSeeds.emplace_back("testseed.slmoin.info");

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,111);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,196);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,239);
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x35, 0x87, 0xCF};
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x35, 0x83, 0x94};

        // human readable prefix to bench32 address
        bech32_hrp = "tpc";

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_test, pnSeed6_test + ARRAYLEN(pnSeed6_test));

        fMiningRequiresPeers = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        m_is_test_chain = true;
        m_is_mockable_chain = false;

        checkpointData = {
            {
                {     0, uint256S("0x00000001f757bb737f6596503e17cd17b0658ce630cc727c0cca81aec47c9f06")},
                { 19080, uint256S("0xb054d63d41852d71b611eaa8eca37d9fddca69b5013cf0966d453402ec8005ce")},
                { 30583, uint256S("0x5179c0c496b5d25ab81ffe14273ea6928c6ff81c0a0d6a83b5d7d41d64886300")},
                { 99999, uint256S("0xa7b03b14b8673683d972ab81775f3e85fea4fe689874b5956183466535dc651c")},
                {219999, uint256S("0x0691bb86c92762c5c4c5a3723585ebeb7ec59310bbb0bdb6666551ab24ad919e")},
                {336000, uint256S("0xf07adf61615c529f7c282b858d13d3e037b197324cb12e0669c461947494c4e3")},
                {372751, uint256S("0x000000000000148db599b217c117b5104f5043c55f6ca2a8a065d9fab9f9bba1")},
                {382019, uint256S("0x3ab75769d7957d9bf0857b5019d0a0e41044fa9ecf30b2f9c32aa457b0864ce5")},
                {408500, uint256S("0x1636ac08b073d26b28fa40243d58dd5deb215752efe094c92c61998e4e9baf3f")},
                {412691, uint256S("0x0e20318be88f07f521453435b37cfc516c3de07264a78ed7170985a1126126ab")},
                {441667, uint256S("0x4636d75163248acd32c212bd1b17f556bdeb3f40316eef662f6736d1c529ae07")},
                {444932, uint256S("0x000000003f7d1f4b55d529fdcf3983c3c8a969ab0900dee41bed0bdaf1c3a9d7")},
            }
        };

        chainTxData = ChainTxData{
            // Data as of block 000000003f7d1f4b55d529fdcf3983c3c8a969ab0900dee41bed0bdaf1c3a9d7 (height 444932)
            1588604853, // * UNIX timestamp of last known number of transactions
            868816,     // * total number of transactions between genesis and that timestamp
                        //   (the tx=... number in the SetBestChain debug.log lines)
            0.003581633 // * estimated number of transactions per second after that timestamp
                        // 868816/(1588604853-1346029522) = 0.003581633
        };
    }
};

/**
 * Regression test
 */

class CRegTestParams : public CChainParams {
public:
    explicit CRegTestParams(const ArgsManager& args) {
        strNetworkID =  CBaseChainParams::REGTEST;
        consensus.BIP16Exception = uint256();
        consensus.BIP34Height = 500; // BIP34 activated on regtest (Used in functional tests)
        consensus.BIP34Hash = uint256();
        consensus.powLimit =            uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"); // ~arith_uint256(0) >> 28;
        consensus.bnInitialHashTarget = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"); // ~arith_uint256(0) >> 29;

        consensus.nTargetTimespan = 7 * 24 * 60 * 60; // two weeks
        consensus.nStakeTargetSpacing = 10 * 60; // 10-minute block spacing
        consensus.nTargetSpacingWorkMax = 12 * consensus.nStakeTargetSpacing; // 2-hour
        consensus.nPowTargetSpacing = consensus.nStakeTargetSpacing;

        consensus.nStakeMinAge = 60 * 60 * 24; // test net min age is 1 day
        consensus.nStakeMaxAge = 60 * 60 * 24 * 90;
        consensus.nModifierInterval = 60 * 20; // Modifier interval: time to elapse before new modifier is computed
        consensus.nCoinbaseMaturity = 60;

        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = true;
        consensus.nRuleChangeActivationThreshold = 108; // 75% for testchains
        consensus.nMinerConfirmationWindow = 144; // Faster than normal for regtest (144 instead of 2016)

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x00");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x00");

        pchMessageStart[0] = 0xcb;
        pchMessageStart[1] = 0xf2;
        pchMessageStart[2] = 0xc0;
        pchMessageStart[3] = 0xef;
        vAlertPubKey = ParseHex("04383862439513e940f6fcbf62d365c162a5256920c2c25b0b4266fdee4a443d71cfe224dbccff6fdb2ea57a37eb0cbec5637ebea06f63c70ca093672fbdc27643");
        nDefaultPort = 9903;
        nPruneAfterHeight = 1000;
        m_assumed_blockchain_size = 0;
        m_assumed_chain_state_size = 0;

        genesis = CreateGenesisBlock(1345083810, 1345090000, 122894938, 0x1d0fffff, 1, 0);

        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x00000001f757bb737f6596503e17cd17b0658ce630cc727c0cca81aec47c9f06"));
        assert(genesis.hashMerkleRoot == uint256S("0x3c2d8f85fab4d17aac558cc648a1a58acff0de6deb890c29985690052c5993c2"));

        vFixedSeeds.clear(); //!< Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();      //!< Regtest mode doesn't have any DNS seeds.

        m_is_test_chain = true;
        m_is_mockable_chain = true;
        checkpointData = {
            {
                {0, uint256S("0x00000001f757bb737f6596503e17cd17b0658ce630cc727c0cca81aec47c9f06")},
            }
        };

        chainTxData = ChainTxData{
            0,
            0,
            0
        };

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,111);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,196);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,239);
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x35, 0x87, 0xCF};
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x35, 0x83, 0x94};

        bech32_hrp = "pcrt";
        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        //fMineBlocksOnDemand = true;
    }
    void UpdateActivationParametersFromArgs(const ArgsManager& args);
};

void CRegTestParams::UpdateActivationParametersFromArgs(const ArgsManager& args)
{
    if (gArgs.IsArgSet("-segwitheight")) {
        int64_t height = gArgs.GetArg("-segwitheight", consensus.SegwitHeight);
        if (height < -1 || height >= std::numeric_limits<int>::max()) {
            throw std::runtime_error(strprintf("Activation height %ld for segwit is out of valid range. Use -1 to disable segwit.", height));
        } else if (height == -1) {
            LogPrintf("Segwit disabled for testing\n");
            height = std::numeric_limits<int>::max();
        }
        consensus.SegwitHeight = static_cast<int>(height);
    }
 }

static std::unique_ptr<const CChainParams> globalChainParams;

const CChainParams &Params() {
    assert(globalChainParams);
    return *globalChainParams;
}

std::unique_ptr<const CChainParams> CreateChainParams(const std::string& chain)
{
    if (chain == CBaseChainParams::MAIN)
        return std::unique_ptr<CChainParams>(new CMainParams());
    else if (chain == CBaseChainParams::TESTNET)
        return std::unique_ptr<CChainParams>(new CTestNetParams());
    else if (chain == CBaseChainParams::REGTEST)
        return std::unique_ptr<CChainParams>(new CRegTestParams(gArgs));
    throw std::runtime_error(strprintf("%s: Unknown chain %s.", __func__, chain));
}

void SelectParams(const std::string& network)
{
    SelectBaseParams(network);
    globalChainParams = CreateChainParams(network);
}
