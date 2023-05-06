#ifndef _CATALOGUE_HASH_CATALOGUE_H_
#define _CATALOGUE_HASH_CATALOGUE_H_

#include <functional>

#include "pouch.h"

namespace catalogue {
    using namespace pouch;

    template<class _T>
    class HashCatalogue {
        private:
            const std::function<_T(const void*)> _getValueLambda;
            FrostWeaveBag<_T, void*> _indexes;

        public:
            HashCatalogue(const std::function<_T(const void*)>& getValueLambda) : _getValueLambda(getValueLambda){

            }

            template<class _Container>
            inline void create(const _Container& container) noexcept {
                const u64 containerSize = container.size();

                for(i32 i = 0; i < containerSize; ++i) {
                    void* dataBucket = (void*)&container[i];

                    const _T& value = _getValueLambda(dataBucket);
                    _indexes.put(value, dataBucket);
                }
            }

            inline void add(const void* dataBucket) noexcept {
                const _T& value = _getValueLambda(dataBucket);
                _indexes.put(value, dataBucket);
            }
            
            inline void erase(const void* dataBucket) {
                const _T& value = _getValueLambda(dataBucket);
                _indexes.erase(value);
            }

            template<class _BucketType>
            inline _BucketType* index(const _T& value) noexcept {
                const std::optional<std::reference_wrapper<void*>> valueOpt = _indexes.get(value);

                if(!valueOpt.has_value())
                    return nullptr;

                return static_cast<_BucketType*>(valueOpt->get());
            }
    };
};

#endif