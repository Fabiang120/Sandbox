#include "miner.h"
#include <unordered_map>
#include <stdexcept>

Miner::Miner(
    const std::string& MinerName,
    const std::string& AlgorithmName,
    double StateElectricityCostPerKwh,
    const std::string& ElectricityCurrency,
    double InitialCost,
    double HashRate,
    double PowerWatts
) : MinerName(MinerName),
    AlgorithmName(AlgorithmName),
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
    std::string AlgorithmName;
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
        CurrentSpec.AlgorithmName,
        StateElectricityCostPerKwh,
        ElectricityCurrency,
        InitialCost,
        CurrentSpec.HashRate,
        CurrentSpec.PowerWatts
    );
}

MiningResult RunMiningSimulation(
    const Miner& MinerObject,
    const Algorithm& AlgorihtmOjbect,
    const Pool& PoolObject,
    double CoinPrice
) {

}


