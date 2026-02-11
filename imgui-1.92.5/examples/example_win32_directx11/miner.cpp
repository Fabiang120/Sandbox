#include "miner.h"
#include <unordered_map>
#include <stdexcept>

Miner::Miner(
    const std::string& MinerName,
    double StateElectricityCostPerKwh,
    const std::string& ElectricityCurrency,
    double InitialCost,
    double HashRate,
    double PowerWatts
) : MinerName(MinerName),
    StateElectricityCostPerKwh(StateElectricityCostPerKwh),
    ElectricityCurrency(ElectricityCurrency),
    InitialCost(InitialCost),
    HashRate(HashRate),
    PowerWatts(PowerWatts)
{
}

MiningResult::MiningResult(
    double CoinsPerDay,
    double RevenuePerDay,
    double PowerCostPerDay,
    double ProfitPerDay
)
    : CoinsPerDay(CoinsPerDay),
    RevenuePerDay(RevenuePerDay),
    PowerCostPerDay(PowerCostPerDay),
    ProfitPerDay(ProfitPerDay)
{
}


// Must set up later
struct MinerSpec {
    std::string SupportedAlgorithm;
    double HashRate;
    double PowerWatts;
};

static const std::unordered_map<std::string, MinerSpec> MinerDatabase = {
    { "Antminer S19", { "SHA-256", 95e12, 3250 } },
    { "Antminer S21", { "SHA-256", 200e12, 3500 } }
};

Miner CreateMiner(
    const std::string& MinerName,
    double StateElectricityCostPerKwh,
    const std::string& ElectricityCurrency,
    double InitialCost
) {
    std::unordered_map<std::string, MinerSpec>::const_iterator it = MinerDatabase.find(MinerName);
    if (it == MinerDatabase.end()) {
        throw std::invalid_argument("Miner not found in database");
    }
    const MinerSpec& CurrentSpec = it->second;

    return Miner(
        MinerName,
        StateElectricityCostPerKwh,
        ElectricityCurrency,
        InitialCost,
        CurrentSpec.HashRate,
        CurrentSpec.PowerWatts
    );
}

// Implement Algorithm and Pool creation tomorrow

MiningResult RunMiningSimulation(
    const Miner& MinerObject,
    const Algorithm& AlgorithmObject,
    const MarketData& MarketDataObject,
    const Pool& PoolObject
) {
    if (MarketDataObject.NetworkHashRate <= 0.0) {
        throw std::invalid_argument("Invalid network hashrate");
    }
    double CoinsPerDay =
        (MinerObject.HashRate / MarketDataObject.NetworkHashRate) *
        AlgorithmObject.BlockReward *
        AlgorithmObject.BlocksPerDay;

    CoinsPerDay *= (1.0 - PoolObject.FeePercent / 100.0);
    CoinsPerDay *= (1.0 - PoolObject.StaleRatePercent / 100.0);

    double RevenuePerDay =
        CoinsPerDay * MarketDataObject.CoinPrice;

    double PowerCostPerDay =
        (MinerObject.PowerWatts / 1000.0) *
        24.0 *
        MinerObject.StateElectricityCostPerKwh;

    double ProfitPerDay =
        RevenuePerDay - PowerCostPerDay;

    return MiningResult(
        CoinsPerDay,
        RevenuePerDay,
        PowerCostPerDay,
        ProfitPerDay
    );
}


