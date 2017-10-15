#ifndef CPP_BITMASK_HPP
#define CPP_BITMASK_HPP

namespace cppbitmasks
{
	template<class MaskT, class FlagT>
	class bitmask
	{
	public:
		bitmask() :
			_val(MaskT())
		{
		}
		bitmask(const MaskT &val) :
			_val(val)
		{
		}

		bitmask(const bitmask &other) :
			_val(other._val)
		{
		}

		bool test(const FlagT &flag) const
		{
			return 0 != (_val & flag);
		}

		bitmask& set(const FlagT &flag)
		{
			_val |= flag;
			return *this;
		}

		bitmask& reset(const FlagT &flag)
		{
			_val &= ~flag;
			return *this;
		}

		bitmask& operator=(const MaskT &val)
		{
			_val = val;
			return *this;
		}

		bitmask& operator=(const bitmask &other)
		{
			_val = other._val;
			return *this;
		}

	private:
		MaskT _val;
	};
}

#endif