#pragma once
#include <iostream>
#include <string>


struct Pool{
    std::string PoolName;
    double FeePercent;
    double StaleRatePercent;
};

struct Algorithm {
    std::string Name;
    double BlockReward;
    double BlocksPerDay;
    double NetworkHashRate;
};

struct Miner {
    std::string MinerName;
    std::string AlgorithmName;
    double StateElectricityCostPerKwh;
    std::string ElectricityCurrency;
    double InitialCost;

    // Internal
    double HashRate;
    double PowerWatts;
    Miner() = delete;
    Miner(
        const std::string& MinerName,
        const std::string& AlgorithmName,
        double StateElectricityCostPerKwh,
        const std::string& ElectricityCurrency,
        double InitialCost,
        double HashRate,
        double PowerWatts
    );
};

struct MiningResult {
    double CoinsPerDay;
    double RevenuePerDay;
    double PowerCostPerDay;
    double ProfitPerDay;
    MiningResult() = delete;
    MiningResult(
        double CoinsPerDay,
        double RevenuePerDay,
        double PowerCostPerDay,
        double ProfitPerDay
    );
};

Miner CreateMiner(
    const std::string& MinerName,
    double StateElectricityCostPerKwh,
    const std::string& ElectricityCurrency,
    double InitialCost
);

MiningResult RunMiningSimulation(
    const Miner& MinerObject,
    const Algorithm& AlgorihtmOjbect,
    const Pool& PoolObject,
    double CoinPrice
);

