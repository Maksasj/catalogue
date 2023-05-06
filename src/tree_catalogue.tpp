#ifndef _CATALOGUE_TREE_CATALOGUE_H_
#define _CATALOGUE_TREE_CATALOGUE_H_

#include <functional>

#include "pouch.h"

namespace catalogue {
    using namespace pouch;

    template<class _T>
    class TreeCatalogue {
        private:
            const std::function<_T(const void*)> _getValueLambda;
            RottenSnag<std::pair<_T, void*>> _indexes;

        public:
            TreeCatalogue(const std::function<_T(const void*)>& getValueLambda) 
                : _getValueLambda(getValueLambda), _indexes(
            [](const std::pair<_T, void*>& a, const std::pair<_T, void*>& b) {
                    return a.first < b.first;
            },  
            [](const std::pair<_T, void*>& a, const std::pair<_T, void*>& b) {
                return a.first == b.first;
            }) {}

            template<class _Container>
            inline void create(const _Container& container) noexcept {
                const u64 containerSize = container.size();

                for(i32 i = 0; i < containerSize; ++i) {
                    void* dataBucket = (void*)&container[i];

                    const _T& value = _getValueLambda(dataBucket);
                    const std::pair<_T, void*> pair = std::make_pair(value, dataBucket);

                    _indexes.put(pair);
                }
            }

            inline void add(const void* dataBucket) noexcept {
                const _T& value = _getValueLambda(dataBucket);
                const std::pair<_T, void*> pair = std::make_pair(value, dataBucket);
                _indexes.put(pair);
            }

            inline void erase(const void* dataBucket) noexcept {
                const _T& value = _getValueLambda(dataBucket);
                const std::pair<_T, void*> pair = std::make_pair(value, dataBucket);
                _indexes.erase(pair);
            }

            template<class _BucketType>
            inline _BucketType* index(const _T& value) noexcept {
                const std::pair<_T, void*>* pairOpt = _indexes.get({value, nullptr});

                if(pairOpt == nullptr)
                    return nullptr;
                
                return static_cast<_BucketType*>(pairOpt->second);
            }
    };
};

#endif