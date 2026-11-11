#include <mint/mint.hpp>

#include <iostream>

namespace mint {
    class arena {
    public:
        // members
        char* buffer = nullptr;

        arena(size_t capacity) {
            buffer = new char[capacity];
        }
        
        // nom-copyable and non-movable
        arena(const arena&) = delete;
        arena& operator=(const arena&) = delete;    
        arena(arena&&) = delete;
        arena& operator=(arena&&) = delete;


        template <typename T, class... Args>
        T* mint(Args&& ...Args) {
            return 0;
        }

        template <typename T>
        T* mint_array(size_t amount) {
            return 0;
        }

        template <typename T, class... Args>
        T* try_mint(Args&& ...Args) {
            return 0;
        }

        template <typename T>
        T* try_mint_array(size_t amount) {
            return 0;
        }


    };
}

int main() {
    mint::arena arena(64 * 1024);

    return 0;
}
