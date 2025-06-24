#ifndef CRAWLING_STRIPE_H
#define CRAWLING_STRIPE_H

#include "effect.h"

class CrawlingStripe : public Effect
{
public:
	CrawlingEffect(Octopus const * octopus);
	~CrawlingEffect() override;

	void animate(long ticks) override;
};

#endif // #ifnder CRAWLING_STRIPE_H
