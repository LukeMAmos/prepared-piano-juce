//Implementation of multichannel versions of the Effects
#include "EffectReverb.h"
#include "EffectFilter.h"
#include "EffectDistortion.h"
#include "EffectDelay.h"

template<typename EffectType>
class MultichannelEffect{
    
public:
    
    template<typename... Args>
    void prepare(int numChannels , Args&&... args){
        
        effects.resize((size_t)numChannels);
        
        for(auto& effect : effects)
            effect.prepare(std::forward<Args>(args)...);
        
    }
    
    template<typename... ParamArgs>
    void setParameters(ParamArgs&&... paramArgs){
        
        for(auto& effect : effects)
            effect.setParameters(std::forward<ParamArgs>(paramArgs)...);
        
    }
    
    float process(int channel , float input){
        
        return effects[(size_t)channel].process(input);
    }
    
    int getNumChannels(){
        return effects.size();
    }
private:
    std::vector<EffectType> effects;
};

