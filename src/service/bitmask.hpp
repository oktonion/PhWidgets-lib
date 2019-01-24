#ifndef CPP_BITMASK_HPP
#define CPP_BITMASK_HPP

namespace cppbitmasks
{
	template<class MaskT, class FlagT, MaskT Mask = ~(MaskT())>
	class bitmask
	{
		bitmask(MaskT val) :
			_val(val)
		{
		}
	public:
		bitmask() :
			_val(MaskT())
		{
		}

		bitmask(const FlagT &flag) :
			_val(flag)
		{
		}

		bitmask(const bitmask &other) :
			_val(other.value())
		{
		}

		inline bool has(const FlagT &flag) const
		{
			return 0 != (value() & flag);
		}

		inline bool has(const bitmask &mask) const
		{
			return 0 != (value() & mask);
		}

		inline bitmask& set(const FlagT &flag)
		{
			_val |= flag;
			return *this;
		}

		inline bitmask& set(const bitmask &mask)
		{
			_val |= mask.value();
			return *this;
		}

		inline bitmask& reset(const FlagT &flag)
		{
			_val &= ~flag;
			return *this;
		}

		inline bitmask& reset(const bitmask &mask)
		{
			_val &= ~mask.value();
			return *this;
		}

		inline bitmask& keep(const FlagT &flag)
		{
			_val &= flag;
			return *this;
		}

		inline bitmask& keep(const bitmask &mask)
		{
			_val &= mask.value();
			return *this;
		}

		inline bitmask& flip(const FlagT &flag)
		{
			_val ^= flag;
			return *this;
		}

		inline bitmask& flip(const bitmask &mask)
		{
			_val ^= mask.value();
			return *this;
		}

		inline bitmask operator|(const FlagT &flag) const
		{
			return *this | bitmask(flag);
		}

		inline bitmask operator|(const bitmask &mask) const
		{
			return value() | mask.value();
		}

		inline bitmask operator&(const FlagT &flag) const
		{
			return *this & bitmask(flag);
		}

		inline bitmask operator&(const bitmask &mask) const
		{
			return value() & mask.value();
		}

		inline bitmask operator^(const FlagT &flag) const
		{
			return *this ^ bitmask(flag);
		}

		inline bitmask operator^(const bitmask &mask) const
		{
			return value() ^ mask.value();
		}

		inline bitmask& operator=(const FlagT &flag)
		{
			*this = bitmask(flag);
			return *this;
		}

		inline bitmask& operator=(const bitmask &other)
		{
			_val = other.value();
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
			return value() == flag;
		}

		inline bool operator==(const bitmask &other) const
		{
			return value() == other.value();
		}

		inline bool operator!=(const FlagT &flag) const
		{
			return value() != flag;
		}

		inline bool operator!=(const bitmask &other) const
		{
			return value() != other.value();
		}

		inline bool operator<(const bitmask &other) const
		{
			return value() < other.value();
		}

		inline bool operator>(const bitmask &other) const
		{
			return value() > other.value();
		}

		inline operator MaskT() const
		{
			return value();
		}

	private:
		MaskT _val;

		inline
		MaskT value() const { return _val & Mask; }
	};


}

template<class MaskT, class FlagT, MaskT Mask>
inline cppbitmasks::bitmask<MaskT, FlagT, Mask>  operator|(const FlagT &flag, const cppbitmasks::bitmask<MaskT, FlagT, Mask> &mask)
{
	return mask | flag;
}

template<class MaskT, class FlagT, MaskT Mask>
inline cppbitmasks::bitmask<MaskT, FlagT, Mask>  operator&(const FlagT &flag, const cppbitmasks::bitmask<MaskT, FlagT, Mask> &mask)
{
	return mask & flag;
}

template<class MaskT, class FlagT, MaskT Mask>
inline cppbitmasks::bitmask<MaskT, FlagT, Mask>  operator^(const FlagT &flag, const cppbitmasks::bitmask<MaskT, FlagT, Mask> &mask)
{
	return mask ^ flag;
}

template<class MaskT, class FlagT, MaskT Mask>
inline cppbitmasks::bitmask<MaskT, FlagT, Mask>  operator==(const FlagT &flag, const cppbitmasks::bitmask<MaskT, FlagT, Mask> &mask)
{
	return mask == flag;
}

template<class MaskT, class FlagT, MaskT Mask>
inline cppbitmasks::bitmask<MaskT, FlagT, Mask>  operator!=(const FlagT &flag, const cppbitmasks::bitmask<MaskT, FlagT, Mask> &mask)
{
	return mask != flag;
}

#endif