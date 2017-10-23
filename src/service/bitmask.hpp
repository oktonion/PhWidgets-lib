#ifndef CPP_BITMASK_HPP
#define CPP_BITMASK_HPP

namespace cppbitmasks
{
	template<class MaskT, class FlagT>
	class bitmask
	{
	public:
		bitmask(MaskT val = MaskT()) :
			_val(val)
		{
		}

		bitmask(const FlagT &flag) :
			_val(flag)
		{
		}

		bitmask(const bitmask &other) :
			_val(other._val)
		{
		}

		inline bool test(const FlagT &flag) const
		{
			return 0 != (_val & flag);
		}

		inline bool test(const bitmask &mask) const
		{
			return 0 != (_val & mask);
		}

		inline bitmask& set(const FlagT &flag)
		{
			_val |= flag;
			return *this;
		}

		inline bitmask& set(const bitmask &mask)
		{
			_val |= mask._val;
			return *this;
		}

		inline bitmask& reset(const FlagT &flag)
		{
			_val &= ~flag;
			return *this;
		}

		inline bitmask& reset(const bitmask &mask)
		{
			_val &= ~mask._val;
			return *this;
		}

		inline bitmask& keep(const FlagT &flag)
		{
			_val &= flag;
			return *this;
		}

		inline bitmask& keep(const bitmask &mask)
		{
			_val &= mask._val;
			return *this;
		}

		inline bitmask& flip(const FlagT &flag)
		{
			_val ^= flag;
			return *this;
		}

		inline bitmask& flip(const bitmask &mask)
		{
			_val ^= mask._val;
			return *this;
		}

		inline bitmask operator|(const FlagT &flag) const
		{
			return _val | flag;
		}

		inline bitmask operator|(const bitmask &mask) const
		{
			return _val | mask._val;
		}

		inline bitmask operator&(const FlagT &flag) const
		{
			return _val & flag;
		}

		inline bitmask operator&(const bitmask &mask) const
		{
			return _val & mask._val;
		}

		inline bitmask operator^(const FlagT &flag) const
		{
			return _val ^ flag;
		}

		inline bitmask operator^(const bitmask &mask) const
		{
			return _val ^ mask._val;
		}

		inline bitmask& operator=(const FlagT &flag)
		{
			_val = flag;
			return *this;
		}

		inline bitmask& operator=(const bitmask &other)
		{
			_val = other._val;
			return *this;
		}

		inline bitmask& operator|=(const FlagT &flag)
		{
			return set(flag);
		}

		inline bitmask& operator|=(const bitmask &other)
		{
			return set(other);
		}

		inline bitmask& operator&=(const FlagT &flag)
		{
			return keep(flag);
		}

		inline bitmask& operator&=(const bitmask &other)
		{
			return keep(other);
		}

		inline bitmask& operator^=(const FlagT &flag)
		{
			return flip(flag);
		}

		inline bitmask& operator^=(const bitmask &other)
		{
			return flip(other);
		}

		inline bool operator==(const FlagT &flag) const
		{
			return test(flag);
		}

		inline bool operator==(const bitmask &other) const
		{
			return test(other);
		}

		inline bool operator!=(const FlagT &flag) const
		{
			return !test(flag);
		}

		inline bool operator!=(const bitmask &other) const
		{
			return !test(other);
		}

		inline bool operator<(const bitmask &other) const
		{
			return _val < other._val;
		}

		inline bool operator>(const bitmask &other) const
		{
			return _val > other._val;
		}

		inline operator const MaskT&() const
		{
			return _val;
		}

	private:
		MaskT _val;
	};
}

template<class MaskT, class FlagT>
inline cppbitmasks::bitmask<MaskT, FlagT>  operator|(const FlagT &flag, const cppbitmasks::bitmask<MaskT, FlagT> &mask)
{
	return mask | flag;
}

template<class MaskT, class FlagT>
inline cppbitmasks::bitmask<MaskT, FlagT>  operator&(const FlagT &flag, const cppbitmasks::bitmask<MaskT, FlagT> &mask)
{
	return mask & flag;
}

template<class MaskT, class FlagT>
inline cppbitmasks::bitmask<MaskT, FlagT>  operator^(const FlagT &flag, const cppbitmasks::bitmask<MaskT, FlagT> &mask)
{
	return mask ^ flag;
}

template<class MaskT, class FlagT>
inline cppbitmasks::bitmask<MaskT, FlagT>  operator==(const FlagT &flag, const cppbitmasks::bitmask<MaskT, FlagT> &mask)
{
	return mask == flag;
}

template<class MaskT, class FlagT>
inline cppbitmasks::bitmask<MaskT, FlagT>  operator!=(const FlagT &flag, const cppbitmasks::bitmask<MaskT, FlagT> &mask)
{
	return mask != flag;
}

#endif