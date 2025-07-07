#ifndef CRAWLING_STRIPE_H
#define CRAWLING_STRIPE_H

#include "octopus_effect.h"

class CrawlingStripe : public OctopusEffect
{
public:
	CrawlingStripe(Octopus * octopus);
	~CrawlingStripe() override;

    void reset() override;
	void animate(long ticks) override;
    void render() override;

protected:
    int tentacleOffsets_[NumTentacles];
    int crawlingSpeed_; // in pixels / second

    int baseLength_;
    int stripeLength_;
    int accentPitch_;

    CHSV baseColor_;
    CHSV stripeColor_;
    CHSV accentColor_;
};

#endif // #ifnder CRAWLING_STRIPE_H
