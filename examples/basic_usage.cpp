#include <mint/mint.hpp>

#include <iostream>

namespace mint {
    class arena {
    public:
        // members
        char* buffer = nullptr;
        size_t offset = 0;
        size_t capacity = 0;

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


        void reset() {
            offset = 0;
        }


        template <typename T, class... Args>
        T* mint(Args&& ...args) {
            // bleh check if an object is destructible with std::is_trivially_destructible_v<T>
            // and handle that properly, later, now its just a simple arena
            static_assert(std::is_trivially_destructible_v<T>, "non-trivially destructible object are not supported!");
            constexpr size_t alignment = alignof(T);
            constexpr size_t size = sizeof(T);

            char* current_ptr = buffer + offset;
            std::size_t space = capacity - offset;
            void* aligned_ptr = current_ptr;

            // align the ptr to the specified alignment
            if (std::align(alignment, size, aligned_ptr, space) == nullptr) {
                throw std::bad_alloc();
            }

            // bump the offset of the arena
            offset = static_cast<char*>(aligned_ptr) - buffer + size;

            return new (aligned_ptr) T(std::forward<Args>(args)...);
        }


        template <typename T>
        T* mint_array(size_t amount) {
            static_assert(std::is_trivially_destructible_v<T>, "non-trivially destructible object are not supported!");
            constexpr size_t alignment = alignof(T);
            constexpr size_t size = sizeof(T);

            void* current_ptr = buffer + offset;
            std::size_t space = capacity - offset;

            const size_t total_size = size * amount;

            // align the ptr to the specified alignment
            if (std::align(alignment, total_size, current_ptr, space) == nullptr) {
                throw std::bad_alloc();
            }

            // bump the offset of the arena
            offset = static_cast<char*>(current_ptr)-buffer + total_size;
            return (T*)current_ptr;
        }

        //template <typename T, class... Args>
        //T* mint_array_ex(size_t amount,  Args&& ...args) {
        //    // TODO: use mint_array then afterwards create a link list (btw if it is possible to compress it because this is just a contiaus array, it would be amazing)
        //    T* start = mint<T>(std::forward<Args>(args)...);
        //    for (size_t counter = 1; counter >= amount; counter++) {
        //        mint<T>(std::forward<Args>(args)...);
        //    }
        //    return 0;
        //}

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
    int* num = arena.mint<int>();
    int* num_array = arena.mint_array<int>(10);
    int stack_num_array[10];
    memcpy(stack_num_array, num_array, 10 * sizeof(int));
    //std::string* str = arena.mint<std::string>();
    printf("hihi  %d\n", *num);
    *num = 10;
    printf("hihi2 %d", *num);

    return 0;
}
