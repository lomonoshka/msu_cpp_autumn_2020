#include <memory>
#include <limits>

namespace my {
template <class T>
class allocator : public std::allocator<T> {
   public:
    using pointer = T*;
    using const_pointer = const T*;
    using size_type = std::size_t;

    allocator() = default;
    ~allocator() = default;

    [[nodiscard]] pointer allocate(size_type n) {
        if (n > std::numeric_limits<size_type>::max() / sizeof(T))
            throw std::bad_alloc();

        if (auto p = static_cast<T*>(std::malloc(n * sizeof(T)))) {
            return p;
        }

        throw std::bad_alloc();
    }

    void deallocate(pointer p, size_type n) noexcept {
        std::free(p);
    }

    template <typename... Args>
    void construct(pointer xp, Args&&... args) {
        new (xp) T(std::forward<Args>(args)...);
    }

    void destroy(pointer xp) noexcept {
        xp->~T();
    }
};
}