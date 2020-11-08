// Copyright (c) 2012-2020 The Slimcoin developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#ifndef SLIMCOIN_KERNELRECORD_H
#define SLIMCOIN_KERNELRECORD_H

#include <uint256.h>
#include <interfaces/wallet.h>

class CWallet;
class CWalletTx;

class KernelRecord
{
public:
    KernelRecord():
        hash(), nTime(0), address(""), nValue(0), idx(0), spent(false), coinAge(0), prevMinutes(0), prevDifficulty(0), prevProbability(0)
    {
    }

    KernelRecord(uint256 hash, int64_t nTime):
            hash(hash), nTime(nTime), address(""), nValue(0), idx(0), spent(false), coinAge(0), prevMinutes(0), prevDifficulty(0), prevProbability(0)
    {
    }

    KernelRecord(uint256 hash, int64_t nTime,
                 const std::string &address,
                 int64_t nValue, int idx, bool spent, int64_t coinAge):
        hash(hash), nTime(nTime), address(address), nValue(nValue),
        idx(idx), spent(spent), coinAge(coinAge), prevMinutes(0), prevDifficulty(0), prevProbability(0)
    {
    }

    static bool showTransaction(bool isCoinbase, int depth);
    static std::vector<KernelRecord> decomposeOutput(interfaces::Wallet &wallet, const interfaces::WalletTx &wtx);


    uint256 hash;
    int64_t nTime;
    std::string address;
    int64_t nValue;
    int idx;
    bool spent;
    int64_t coinAge;

    std::string getTxID();
    int64_t getAge() const;
    double getProbToMintStake(double difficulty, int timeOffset = 0) const;
    double getProbToMintWithinNMinutes(double difficulty, int minutes);
protected:
    int prevMinutes;
    double prevDifficulty;
    double prevProbability;
};

#endif // SLIMCOIN_KERNELRECORD_H
