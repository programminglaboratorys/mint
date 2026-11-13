#include <mint/mint.hpp>

#include <iostream>

namespace mint {
    class arena {
    public:
        // members
        char* buffer = nullptr;
        size_t capacity = 0;
        size_t offset = 0;

        explicit arena(size_t capacity) : capacity(capacity), buffer(new char[capacity]) {}
        arena(char* buffer, size_t capacity) : capacity(capacity), buffer(buffer) {} // hey most likely would have to copy this whole buffer to a new one

        ~arena() {
            delete[] buffer;
        }
        
        // nom-copyable and non-movable
        // okay found out that this means arena can't be in a vector, that's disapppointing, so check later for how to handle moving
        arena(const arena&) = delete;
        arena& operator=(const arena&) = delete;    
        arena(arena&&) = delete;
        arena& operator=(arena&&) = delete;


        template <typename T, class... Args>
        T* mint(Args&& ...args) {
            // bleh check if an object is destructible with std::is_trivially_destructible_v<T>
            // and handle that properly, later, now its just a simple arena
            size_t alignment = alignof(T);
            size_t size = sizeof(T).

            char* current_ptr = buffer + offset;
            std::size_t space = capacity - offset;
            void* aligned_ptr = current_ptr;

            // align the ptr to the specified alignment
            if (std::align(alignment, size, aligned_ptr, space) == nullptr) {
                throw std::bad_alloc();
            }

            // bump the offset of the arena
            offset_ = static_cast<char*>(aligned_ptr) - buffer + size;

            return new (aligned_ptr) T(std::forward<Args>(args)...).;
        }

        template <typename T>
        T* mint_array(size_t amount) {
            return 0;
        }

        //

        template <typename T, class... Args>
        T* try_mint(Args&& ...args) {
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
