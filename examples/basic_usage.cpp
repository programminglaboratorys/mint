#include <mint/mint.hpp>

#include <iostream>

namespace mint {
    class arena {
    public:
        // members
        char* buffer = nullptr;
        size_t capacity = 0;
        size_t offset = 0;

        arena(size_t capacity) : capacity(capacity), buffer(new char[capacity]) {}
        arena(char* buffer, size_t capacity) : capacity(capacity), buffer(buffer) {}

        
        // nom-copyable and non-movable
        // okay found out that this means arena can't be in a vector, that's disapppointing, so check other stuff
        arena(const arena&) = delete;
        arena& operator=(const arena&) = delete;    
        arena(arena&&) = delete;
        arena& operator=(arena&&) = delete;


        template <typename T, class... Args>
        T* mint(Args&& ...Args) {

            return new (buffer + offset) T;
        }

        template <typename T>
        T* mint_array(size_t amount) {
            return 0;
        }

        //

        template <typename T, class... Args>
        T* try_mint(Args&& ...Args) {
            return 0;
        }

        template <typename T>
        T* try_mint_array(size_t amount) {
            return 0;
        }


        //



    };
}

int main() {
    mint::arena arena(64 * 1024);

    return 0;
}
