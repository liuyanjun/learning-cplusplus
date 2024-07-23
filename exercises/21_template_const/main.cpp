#include "../exercise.h"
#include <vector>
#include <cstring>
// READ: 模板非类型实参 <https://zh.cppreference.com/w/cpp/language/template_parameters#%E6%A8%A1%E6%9D%BF%E9%9D%9E%E7%B1%BB%E5%9E%8B%E5%AE%9E%E5%8F%82>

template<unsigned int N, class T>
struct Tensor {
    unsigned int shape[N];
    T *data;
    unsigned int strides[N];
    unsigned int size;

    Tensor(unsigned int const shape_[N]) {
        size = 1;
        for(unsigned int i = 0; i< N; i++){
            size *= shape_[i];
        }
        // TODO: 填入正确的 shape 并计算 size
        std::cout << "data array size=" << size << std::endl;
        data = new T[size];
        memset(data, 0, size * sizeof(T));

        memcpy(shape, shape_, N * sizeof(unsigned int));
        for(unsigned int i = 0; i< N; i++){
            std::cout << "data shape = " <<  shape[i]<<std::endl;
        }
        calculateStrides();        
    }
    ~Tensor() {
        delete[] data;
    }

    // 为了保持简单，禁止复制和移动
    Tensor(Tensor const &) = delete;
    Tensor(Tensor &&) noexcept = delete;

    T &operator[](unsigned int const indices[N]) {
        unsigned int idx = data_index(indices);
        std::cout<< "data_index="<< idx<<std::endl;
        ASSERT(idx < size, "out of boundary");
        return data[idx];
    }
    T const &operator[](unsigned int const indices[N]) const {
        return data[data_index(indices)];
    }

private:
    unsigned int data_index(unsigned int const indices[N]) const {
        unsigned int index = 0;
        for (unsigned int i = 0; i < N; ++i) {
            //ASSERT(indices[i] < shape[i], "out of boundary");
            std::cout<< ">>data_index = " << indices[i] << ",stride="<<  strides[i] << std::endl;
            // TODO: 计算 index
            index += strides[i] * indices[i];
            
        }
        return index;
    }

    void calculateStrides(){
        
        unsigned int value = 1;
        
        for (int i = N-1; i >= 0; i--) {
        
            strides[i] = value;
            std::cout << "stride=" << strides[i] << ", shape[i]="<< shape[i] << std::endl;
            value = value * shape[i];
            
        }

        
        // for (unsigned int j = 0; j < N; j++) {
        //     //std::cout << "stride = " << strides[i] << ", ";
        //     printf("stride = %d\n", strides[j]);
        // }
    }
};

// ---- 不要修改以下代码 ----
int main(int argc, char **argv) {
    {
        unsigned int shape[]{2, 3, 4, 5};
        std::cout<< "first start"<<std::endl;
        auto tensor = Tensor<4, unsigned int>(shape);
        std::cout<< "first step"<<std::endl;
        unsigned int i0[]{0, 0, 0, 0};
        tensor[i0] = 1;
        std::cout<< "second step"<<std::endl;
        ASSERT(tensor[i0] == 1, "tensor[i0] should be 1");

        unsigned int i1[]{1, 2, 3, 4};
        tensor[i1] = 2;
        ASSERT(tensor[i1] == 2, "tensor[i1] should be 2");
    }
    {
        unsigned int shape[]{7, 8, 128};
        auto tensor = Tensor<3, float>(shape);

        unsigned int i0[]{0, 0, 0};
        tensor[i0] = 1.f;
        ASSERT(tensor[i0] == 1.f, "tensor[i0] should be 1");

        unsigned int i1[]{3, 4, 99};
        tensor[i1] = 2.f;
        ASSERT(tensor[i1] == 2.f, "tensor[i1] should be 2");
    }
    return 0;
}
