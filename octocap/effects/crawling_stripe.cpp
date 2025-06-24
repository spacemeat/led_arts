#include "crawling_stripe.cpp"


CrawlingEffect::CrawlingEffect(Octopus const * octopus)
: Effect(octopus)
{

}


CrawlingEffect::~CrawlingEffect() override
{
}

void animate(long ticks) override
{
	auto idx = _octopus->_tentacles[0]._frame_buffer_start

}

