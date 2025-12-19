#include <cstddef>
#include <util2/C/macro.h>


template<typename T>
struct runtimeConstantPointer
{
public:
    runtimeConstantPointer<T>& operator=(T* pointer) {
        modifyOnce(pointer);
        return *this;
    }
    const runtimeConstantPointer<T>& operator=(const T* pointer) {
        modifyOnce(pointer);
        return *this;
    }
    ~runtimeConstantPointer<T>() {
        m_ptr = nullptr;
        m_modified = false;
        return;
    };



    runtimeConstantPointer<T>() = default;
    runtimeConstantPointer<T>(const runtimeConstantPointer<T>&) = delete;
    runtimeConstantPointer<T>(runtimeConstantPointer<T>&&) 	    = delete;
    runtimeConstantPointer<T>& operator=(const runtimeConstantPointer<T>& ) = delete;
    runtimeConstantPointer<T>& operator=(      runtimeConstantPointer<T>&&) = delete;

    T& operator[](std::size_t index) {
        return m_ptr[index];
    }
    const T& operator[](std::size_t index) const {
        return m_ptr[index];
    }

    
private:
    bool m_modified = false;
    T*   m_ptr 		= nullptr;


    void modifyOnce(const T* ptr) {
        if( unlikely(!m_modified) ) {
            m_ptr      = ptr;
            m_modified = true;
        }
        return;
    }
};