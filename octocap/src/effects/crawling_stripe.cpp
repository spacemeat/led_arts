#include "../octopus.h"
#include "crawling_stripe.h"

#ifndef ARDUINO
#include <ostream>
#endif

CrawlingStripe::CrawlingStripe(Octopus * octopus)
: OctopusEffect(octopus)
{
}


CrawlingStripe::~CrawlingStripe()
{
}

void CrawlingStripe::reset()
{
    // determine offsets for each tentacle
	for (int i = 0; i < NumTentacles; ++i)
    {
        tentacleOffsets_[i] = random(NumLedsPerTentacle * 1024);
    }

    int crawlingUpOrDown = 1 - 2 * random(2);
    crawlingSpeed_ = 10 + random(40) * crawlingUpOrDown;

    baseLength_ = 3 + random(3);
    stripeLength_ = 1 + random(2);
    accentPitch_ = 12 + random(12);
    
    // determine colors and speeds
    baseColor_ = makeRandomColor();
    stripeColor_ = makeRandomColor(baseColor_);
    accentColor_ = makeRandomColor(baseColor_);
}

void CrawlingStripe::animate(long ticks)
{
    int crawl = ticks * crawlingSpeed_;
	for (int i = 0; i < NumTentacles; ++i)
    {
        tentacleOffsets_[i] += crawl;
        tentacleOffsets_[i] = (tentacleOffsets_[i] + NumLedsPerTentacle * 1024) % (NumLedsPerTentacle * 1024);
    }
}

void CrawlingStripe::render()
{
    for (int p = 0; p < NumLedsPerTentacle; ++p)
    {
        CHSV c = baseColor_;
        if ((p % (baseLength_ + stripeLength_)) >= baseLength_)
            { c = stripeColor_; }
        
        if (p % accentPitch_ == 0)
            { c = accentColor_; }

        for (int i = 0; i < NumTentacles; ++i)
        {
            auto po = (tentacleOffsets_[i] >> 10) + p;
            po %= NumLedsPerTentacle;
            auto idx = octopus_->_tentacles[i]._frame_buffer_start + po;
            controller_->set_pixel(this, idx, c);
        }
    }
}

void CrawlingStripe::report() const
{
	//for (int i = 0; i < NumTentacles; ++i)
    //{
    //    std::cout << "tentacle " << i << " offset: " << tentacleOffsets_[i] << "   \n";
    //}

    //std::cout << "base color: " << baseColor_ << "   \n";
    //std::cout << "stripe color: " << stripeColor_ << "   \n";
    //std::cout << "accent color: " << accentColor_ << "   \n";
}

