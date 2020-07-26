#ifndef BIG_INT_H
# define BIG_INT_H
#define DEFAULT_NUM_SIZE 4
#define MAX_UNIT_VALUE 4294967295

#include <glob.h>
#include <vector>
#include <sys/types.h>
#include <iostream>

typedef u_int32_t u_int;

class	BigInt{
	size_t	num_size;
	size_t	buff_size;
	std::vector<u_int> num;
	bool sign;

	void						check_size();
	static BigInt				add(const BigInt &left, const BigInt &right);
	static BigInt				my_abs(const BigInt &num);
	void						erase_extra_zeros();
	[[nodiscard]] BigInt		reverse() const;
	BigInt operator<<(const u_int &other) const;
public:
	BigInt();
	BigInt(int n);
	BigInt(const BigInt &copied);
	BigInt(BigInt &&moved) noexcept;
	~BigInt();
	BigInt	&operator=(const BigInt &copied);
	BigInt	&operator=(BigInt &&moved) noexcept;
	BigInt	&operator=(const int &copied);
	BigInt	&operator=(int &&moved) noexcept;
	bool    operator==(const BigInt &other) const;
	bool    operator!=(const BigInt &other) const;
	bool    operator<(const BigInt &other) const;
	bool    operator<=(const BigInt &other) const;
	bool    operator>(const BigInt &other) const;
	bool    operator>=(const BigInt &other) const;
	bool    operator==(const int &other) const;
	bool    operator!=(const int &other) const;
	bool    operator<(const int &other) const;
	bool    operator<=(const int &other) const;
	bool    operator>(const int &other) const;
	bool    operator>=(const int &other) const;

	BigInt operator+(const BigInt &other) const;
	BigInt operator+(const int &other) const;
	BigInt operator-() const;
	BigInt operator-(const BigInt &other) const;
	BigInt operator-(const int &other) const;
	BigInt operator*(const int &other) const;
	BigInt operator*(const u_int &other) const;
	BigInt operator*(const BigInt &other) const;
	BigInt operator/(const u_int &other) const;
	BigInt operator/(const BigInt &other) const;
	void operator+=(const BigInt &other);
	void operator-=(const BigInt &other);
	void operator*=(const BigInt &other);
	void operator++();

	friend std::ostream &operator<<(std::ostream &out, const BigInt &big_int);
	friend std::istream &operator>>(std::istream &in, BigInt &big_int);
};

#endif //BIG_INT_H
