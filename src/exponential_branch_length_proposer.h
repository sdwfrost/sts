#ifndef STS_MOVES_EXPONENTIAL_BRANCH_LENGTH_PROPOSER_HPP
#define STS_MOVES_EXPONENTIAL_BRANCH_LENGTH_PROPOSER_HPP

#include "smctc.hh"

#include "state.h"
#include "base_branch_length_proposer.h"

namespace sts
{
namespace moves
{

/// \class Exponential_branch_length_proposer
/// \brief Propose branch lengths from an exponential distribution.
class Exponential_branch_length_proposer : public Base_branch_length_proposer
{
public:
    /// Instantiate a new BL proposer where branch lengths are drawn from an exponential distribution with mean
    /// \c mean.
    /// \param mean Mean of exponential distribution
    explicit Exponential_branch_length_proposer(double mean) : mean(mean) {};
    double log_proposal_density(double);

    /// Mean of exponential distribution
    double mean;
protected:
    double propose_bl(smc::rng *);
};

} // namespace moves
} // namespace sts

#endif // STS_MOVES_EXPONENTIAL_BRANCH_LENGTH_PROPOSER_HPP