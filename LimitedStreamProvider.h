#ifndef LIMITED_STREAM_PROVIDER_H
#define LIMITED_STREAM_PROVIDER_H

#include "StreamProvider.h"

template<typename T, template<typename> class Pointer>
class LimitedStreamProvider : public StreamProvider<T, Pointer> {

public:
    LimitedStreamProvider(StreamProviderPtr<T, Pointer> source, size_t limit)
        : source_(std::move(source)), remaining_(limit) {}

    Pointer<T> get() override {
        return std::move(current_);
    }

    bool advance() override {
        if(remaining_ == 0) {
            return false;
        }
        if(source_->advance()) {
            current_ = source_->get();
            remaining_--;
            return true;
        }
        return false;
    }

private:
    StreamProviderPtr<T, Pointer> source_;
    Pointer<T> current_;
    std::size_t remaining_;

};

#endif
