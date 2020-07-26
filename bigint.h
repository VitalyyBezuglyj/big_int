//
// Created by Vitaly on 02.04.2019.
//

#ifndef BIGINT_BIGINT_H
#define BIGINT_BIGINT_H
#include <iostream>

using unit = char;

class BigInt {
    size_t size; //size of filled part
    size_t size_num; //size of *number
    char sign;
    unit *number;

    static const char nan = 31;

    static bool isDigit(unit u) {
        return u < 48 ? false : u < 58;
    }

    static unit *intToUnits(int64_t my_int, size_t &num_size, size_t &buff_size) {
        size_t size_of_int = sizeof(int);
        buff_size = (((size_of_int * 8 - 1) / 10) + 1) * 3;
        char *str = new unit[buff_size];
        for (size_t i = 0; i < buff_size; ++ i) {
            str[i] = static_cast<char>(my_int % 10) + '0';
            my_int /= 10;
        }
        size_t k = buff_size-1;
        while (str[k] == '0') {
            str[k] = nan;
            k --;
        }
        num_size = k+1;
        /* num_size = 0;
         new_num[0] = '0';
         for (size_t i = k; i < buff_size; ++ i) {
             ch = str[i];
             new_num[num_size] = ch;
             num_size ++;
         }
         for (size_t i = num_size; i < buff_size; ++ i) {
             new_num[i] = nan;
         }
         num_size = num_size == 0 ? 1 : num_size;
         delete[]str;*/
        return str;
    }

    static unit *sum(const unit *left, const unit *right, size_t left_size, size_t right_size) {
        /*std::cout << "Left : " << std::endl;
        for (size_t i = 0; i < left_size; ++ i) {
            std::cout << left[left_size - 1 - i] << " ";
        }
        std::cout << std::endl;
        std::cout << "Right : " << std::endl;
        for (size_t i = 0; i < right_size; ++ i) {
            std::cout << right[right_size - 1 - i] << " ";
        }
        std::cout << std::endl;*/

        size_t sum_size = (left_size > right_size ? left_size : right_size) + 1;
        unit *res = new unit[sum_size];
        unit res_u;
        unit rem = 0;
        unit l = 0;
        unit r = 0;
        for (size_t i = 0; i < sum_size; ++ i) {
            l = i >= left_size ? '0' : left[i];
            r = i >= right_size ? '0' : right[i];
            res_u = rem + (l - '0') + (r - '0');
            rem = res_u / 10;
            res_u = res_u % 10 + '0';
            res[i] = res_u;
        }

       /* for (size_t i = 0; i < sum_size; ++ i) {
            std::cout << res[sum_size - 1 - i] << " ";
        }
        std::cout << std::endl;*/

        return res;
    }

    static unit *additionalyNum(const unit *num, size_t size) {
        unit *res = new unit[size];
        for (size_t i = 0; i < size; ++ i) {
            res[i] = '9' - num[i] + '0';
            std::cout << "# " << i << " = " << res[i] << " ";
        }
        std::cout << std::endl;
        return res;
    }

    void resize_num(size_t s) {
        unit *new_number = new unit[s];
        std::copy(number, number + size_num, new_number);
        for (size_t i = 0; i < s; ++ i) {
            new_number[i] = nan;
        }
        delete[] number;
        number = new_number;
        size_num = s;
    }

    void check_size() {
        if ((size_num - size < 16) && (size_num != 0)) {
            return;
        }
        resize_num(size_num + 16);
    }

    unit getINumDigit(size_t i) const {
        return i < size ? number[i] : '0';
    }

public:

    BigInt() : size(0), size_num(0), sign(0), number(nullptr) {}

    BigInt(const BigInt &copied) : size(copied.size), size_num(copied.size_num), sign(copied.sign), number(nullptr) {
        number = new unit[size_num];
        std::copy(copied.number, copied.number + copied.size_num, number);
    }

    BigInt(BigInt &&moved) noexcept : size(moved.size), size_num(moved.size_num), sign(moved.sign),
                                      number(moved.number) {
        moved.size = 0;
        moved.size_num = 0;
        moved.sign = 0;
        moved.number = nullptr;
    }

    BigInt(const int64_t &copied) {
        int64_t copy = copied;
        size = 0;
        size_num = 0;
        sign = copy > 0 ? 1 : - 1;
        copy *= sign;
        size_t num_size = 0;
        size_t buff_size = 0;
        number = intToUnits(copy, num_size, buff_size);
        size = num_size;
        size_num = buff_size;

    }

    BigInt(int64_t &&moved) {
        //int radix = 10;
        size = 0;
        size_num = 0;
        sign = moved > 0 ? 1 : - 1;
        moved *= sign;
        size_t num_size = 0;
        size_t buff_size = 0;
        number = intToUnits(moved, num_size, buff_size);
        size = num_size;
        size_num = buff_size;
        moved = 0;
    }

    ~BigInt() {
        delete[] number;
        std::cout << "~" << std::endl;
    }

    BigInt &operator=(const BigInt &copied) {
        if (this == &copied) {
            return *this;
        }
        size = copied.size;
        size_num = copied.size_num;
        unit *temp = new unit[size_num];
        delete[] number;
        number = temp;
        sign = copied.sign;
        std::copy(copied.number, copied.number + copied.size_num, number);
        return *this;
    }

    BigInt &operator=(BigInt &&moved) noexcept {
        if (this == &moved) {
            return *this;
        }
        delete[] number;
        size = moved.size;
        size_num = moved.size_num;
        sign = moved.sign;
        number = moved.number;
        moved.size = 0;
        moved.size_num = 0;
        moved.sign = 0;
        moved.number = nullptr;
        return *this;
    }

    BigInt &operator=(const int64_t &copied) {
        int64_t copy = copied;
        size = 0;
        size_num = 0;
        sign = copy > 0 ? 1 : - 1;
        copy *= sign;
        size_t num_size = 0;
        size_t buff_size = 0;
        delete[]number;
        number = intToUnits(copy, num_size, buff_size);
        size = num_size;
        size_num = buff_size;
        return *this;
    }

    BigInt &operator=(int64_t &&moved) noexcept {
        size = 0;
        size_num = 0;
        sign = moved > 0 ? 1 : - 1;
        moved *= sign;
        size_t num_size = 0;
        size_t buff_size = 0;
        delete[]number;
        number = intToUnits(moved, num_size, buff_size);
        size = num_size;
        size_num = buff_size;
        moved = 0;
        return *this;
    }

    bool operator==(const BigInt &other) const {
        if (this == &other) {
            return true;
        }
        bool simple = (size == other.size) && (size_num == other.size_num) && (sign == other.sign);
        if (! simple) {
            return false;
        }
        for (size_t i = 0; i < size; ++ i) {
            if (number[size - i - 1] != other.number[size - i - 1]) {
                return false;
            }
        }
        return true;

    }

    bool operator!=(const BigInt &other) const {
        return ! (this->operator==(other));
    }

    bool operator<(const BigInt &other) const {
        if (this == &other) {
            return false;
        }

        bool simple = (size > other.size) || (sign > other.sign);
        if (simple) {
            return false;
        }
        bool simple_2 = (sign < other.sign) || ((size < other.size) && (sign == other.sign));
        if (simple_2) {
            return true;
        }
        for (size_t i = 0; i < size; ++ i) {
            if (number[size - i - 1] < other.number[size - i - 1]) {
                return true;
            }
        }
        return false;
    }

    bool operator<=(const BigInt &other) const {
        if (this == &other) {
            return false;
        }
        bool simple = (size > other.size) || (sign > other.sign);
        if (simple) {
            return false;
        }
        bool simple_2 = (sign < other.sign) || ((size < other.size) && (sign == other.sign));
        if (simple_2) {
            return true;
        }
        for (size_t i = 0; i < size; ++ i) {
            if (number[size - 1 - i] > other.number[size - 1 - i]) {
                return false;
            }
        }
        return true;
    }

    bool operator>(const BigInt &other) const {
        return ! this->operator<=(other);
    }

    bool operator>=(const BigInt &other) const {
        return ! this->operator<(other);
    }

    bool operator==(const int64_t &my_int) const {
        BigInt other(my_int);
        return this->operator==(other);
    }

    bool operator!=(const int64_t &other) const {
        return ! (this->operator==(other));
    }

    bool operator<(const int64_t &my_int) const {
        BigInt other(my_int);
        return this->operator<(other);
    }

    bool operator<=(const int64_t &my_int) const {
        BigInt other(my_int);
        return this->operator<=(other);
    }

    bool operator>(const int64_t &my_int) const {
        BigInt other(my_int);
        return this->operator>(other);
    }

    bool operator>=(const int64_t &my_int) const {
        BigInt other(my_int);
        return this->operator>=(other);
    }

    BigInt operator+(const BigInt &other) const {
        BigInt res;
        res.size_num = (size > other.size ? size : other.size) + 1;
        res.size = res.size_num;
        unit *temp;
        if (sign == other.sign) {
            res.sign = sign;
            res.number = sum(number, other.number, size, other.size);
            size_t s = res.size - 1;
            while (res.number[s] == '0') {
                res.size --;
                s --;
            }
        } else {
            BigInt left(*this);
            left.sign = 1;
            BigInt right(other);
            right.sign = 1;
            if (left < right) {
                temp = additionalyNum(right.number, right.size);
                res.number = sum(left.number, temp, left.size, right.size);
                size_t s = res.size - 1;
                while (res.number[s] == '0') {
                    res.size --;
                    s --;
                }
                delete[]temp;
                temp = res.number;
                res.number = additionalyNum(temp, res.size);
                while (res.number[s] == '0') {
                    res.size --;
                    s --;
                }
                delete[]temp;
                res.sign = other.sign;
            } else {
                temp = additionalyNum(left.number, left.size);
                res.number = sum(right.number, temp, right.size, left.size);
                size_t s = res.size - 1;
                while (res.number[s] == '0') {
                    res.size --;
                    s --;
                }

                delete[]temp;
                temp = res.number;
                res.number = additionalyNum(temp, res.size);
                while (res.number[s] == '0') {
                    res.size --;
                    s --;
                }
                delete[]temp;
                res.sign = sign;
            }
        }
        return res;
    }

    BigInt operator-() const {
        BigInt new_big_int(*this);
        new_big_int.sign *= - 1;
        return new_big_int;
    }

    BigInt operator-(const BigInt &other) const {
        return this->operator+(- other);
    }

    friend std::ostream &operator<<(std::ostream &out, const BigInt &big_int) {
        //std::cout << "&operator<<";
        if (big_int.sign < 0) {
            out << '-';
        }
        size_t s = big_int.size;
        for (size_t i = 0; i < s; ++ i) {
            //std::cout << static_cast<int64_t>(big_int.number[i]) << " ";
            out << big_int.number[s - i - 1];
        }
        //std::cout << std::endl << "Size : " << big_int.size << "  Size_num : " << big_int.size_num << std::endl;
        return out;
    }

    friend std::istream &operator>>(std::istream &in, BigInt &big_int) {
        unit u;
        size_t s = 0;
        big_int.size = 0;
        std::cin.get();
        std::cin.unget();
        int64_t first = in.peek();
        if ((first == 45) || (first == 43)) {
            big_int.sign = static_cast<char>(44 - first);
            in.get();
        } else {
            big_int.sign = 1;
        }
        while (in.peek()) {
            in.get(u);
            if ((u == ' ') || (u == '\n')) {
                break;
            }
            if (! isDigit(u)) {
                break; //exception ?
            }
            big_int.check_size();
            big_int.number[s] = u;
            s ++;
            //std::cout << "# " << s << " = " << u << " ";
            big_int.size ++;
        }
        size_t ss = big_int.size;
        unit *ptr = new unit[ss];
        for (size_t i = 0; i < ss; ++ i) {
            ptr[i] = big_int.number[ss - 1 - i];
        }
        delete[]big_int.number;
        big_int.number = ptr;
        big_int.size_num = ss;
        //std::cout << " cin OK" << std::endl;
        return in;
    }
};

/*
int main() {
    std::cout << "Hello, World!" << std::endl;
    int64_t x = 9535;
    BigInt a;
    BigInt b;
    std::cin >> a >> b;
    // a = x;
    std::cout << "a = " << a << "  b = " << b << std::endl;
    //a = - a;
    std::cout << "b + a = " << (b + a) << std::endl;

    */
/*unit u;
    std::cin.peek();
    std::cout << "Enter the char : " ;
    std:: cout << std::cin.peek() << std::endl;
    std::cin.get(u);
    std::cout << u;*//*

    std::cin.get();
    std::cin.get();
    return 0;
}
*/

#endif //BIGINT_BIGINT_H
