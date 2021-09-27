#pragma once
#include <vector>
//#define get_array_element_def(X)
namespace tu
{

	//////////////////////////////////////////////////////////////////////////////

	/**
	 * \brief value type of rank
	 */
	typedef int rank_t;

	//////////////////////////////////////////////////////////////////////////////

	/**
	 * \brief typename -> typename*
	 * \tparam _Value_ptr_type value type / òèï âåëè÷èíû
	 */
	template<typename _Value_ptr_type> using Ptr = _Value_ptr_type*;

	/**
	 * \brief typename -> typename&
	 * \tparam _Value_ptr_type value type / òèï âåëè÷èíû
	 */
	template<typename _Value_ptr_type> using Ref = _Value_ptr_type&;


	//////////////////////////////////////////////////////////////////////////////

	/**
	* \brief get the sum of arguments / ïîëó÷èòü êîëè÷åñòâî àðãóìåíòîâ
	* \param _Args args / àðãóìåíòû
	* \return the sum of arguments / ñóììà àðãêìåíòîâ
	*/
	template<typename... _Args>
	constexpr inline rank_t argsum(_Args... args)
	{
		return sizeof...(args);
	}

	//////////////////////////////////////////////////////////////////////////////

	/**
	 * \brief multi-dimension vector / ìíîãîìåðíûé âåêòîð
	 * \tparam _Value_type value type
	 * \tparam _Dimension_rank rank
	 */
	template <typename _Value_type, rank_t _Dimension_rank>
	struct multi_dimension_vector_str
	{
		/**
		 * \brief multi-dimension vector / ìíîãîìåðíûé âåêòîð
		 */
		typedef std::vector<typename multi_dimension_vector_str
			<_Value_type, _Dimension_rank - 1>::type> type;
	};

	/**
	 * \brief multi-dimension vector / ìíîãîìåðíûé âåêòîð
	 * \tparam _Value_type value type
	 * \tparam _Dimension_rank rank
	 */
	template<typename _Value_type>
	struct multi_dimension_vector_str<_Value_type, 0>
	{
		/**
		 * \brief multi-dimension vector / ìíîãîìåðíûé âåêòîð
		 */
		typedef _Value_type type;
	};


	/**
	 * \brief multi-dimension vector / ìíîãîìåðíûé âåêòîð
	 * \tparam _Value_type value type
	 * \tparam _Dimension_rank rank
	 */
	template <typename _Value_type, rank_t _Dimension_rank>
	using multi_dimension_vector = \
		typename multi_dimension_vector_str<_Value_type, _Dimension_rank>::type;

	/**
	* \brief variadic args to array / ìàññèâ âàðèàòèâíûõ àðãóìåíòîâ
	*/
	template<typename _Value_type, _Value_type... _Args>
	struct variadic_args_array_str
	{
		/**
		* \brief array of variadic args / ìàññèâ âàðèàòèâíûõ àðãóìåíòîâ
		*/
		static _Value_type data[argsum(_Args...)];
	};

	/**
	 * \brief array of variadic args / ìàññèâ âàðèàòèâíûõ àðãóìåíòîâ
	 */
	template<typename _Value_type, _Value_type... _Args>
	_Value_type variadic_args_array_str<_Value_type, _Args...> \
		::data[argsum(_Args...)] =
	{
		_Args...
	};

	//////////////////////////////////////////////////////////////////////////////

	/**
	 * \brief return last arg
	 * \param arg first arg
	 * \param args other args
	 */
	template<typename _Value_type, _Value_type _Arg, _Value_type... _Args>
	struct variadic_arg_last
	{
		/**
		 * \brief last arg
		 */
		static const inline _Value_type value = \
			variadic_arg_last<_Value_type, _Args...>::value;
	};

	/**
	 * \brief return last arg
	 * \param arg first arg
	 * \param args other args
	 */
	template<typename _Value_type, _Value_type _Arg>
	struct variadic_arg_last<_Value_type, _Arg>
	{
		/**
		 * \brief last arg
		 */
		static const inline _Value_type value = _Arg;
	};

	/**
	 * \brief return first arg
	 * \param arg first arg
	 * \param args other args
	 */
	template<typename _Value_type, _Value_type _Arg, _Value_type... _Args>
	struct variadic_arg_first
	{
		/**
		 * \brief first arg
		 */
		static const inline _Value_type value = _Arg;
	};

	/**
	 * \brief return first arg
	 * \param arg first arg
	 * \param args other args
	 */
	template<typename _Value_type, _Value_type _Arg>
	struct variadic_arg_first<_Value_type, _Arg>
	{
		/**
		 * \brief first arg
		 */
		static const inline _Value_type value = _Arg;
	};

	//////////////////////////////////////////////////////////////////////////////

	/**
	 * \brief return last arg
	 * \param arg first arg
	 * \param args other args
	 * \return last arg
	 */
	template<typename _Arg>
	constexpr inline _Arg variadic_func_arg_last(_Arg arg)
	{
		return arg;
	};

	/**
	 * \brief return last arg
	 * \param arg first arg
	 * \param args other args
	 * \return last arg
	 */
	template<typename _Arg, typename... _Args>
	constexpr inline _Arg variadic_func_arg_last(_Arg arg, _Args... args)
	{
		return variadic_func_arg_last(args...);
	};

	/**
	 * \brief return first arg
	 * \param arg first arg
	 * \param args other args
	 * \return first arg
	 */
	template<typename _Arg>
	inline constexpr _Arg variadic_func_arg_first(_Arg arg)
	{
		return arg;
	};

	/**
	 * \brief return first arg
	 * \param arg first arg
	 * \param args other args
	 * \return first arg
	 */
	template<typename _Arg, typename... _Args>
	inline constexpr _Arg variadic_func_arg_first(_Arg arg, _Args... args)
	{
		return arg;
	};

	//////////////////////////////////////////////////////////////////////////////

	/**
	 * \brief returns a given number of pointers to pointers of type
	 * \brief âîçâðàùàåò çàäàííîå êîëè÷åñòâî óêàçàòåëåé íà óêàçàòåëè òèïà
	 * \tparam _Value_ptr_type value type
	 * \tparam _Rank rank
	 */
	template<typename _Value_ptr_type, rank_t _Rank>
	struct PtrInfStr
	{
		typedef typename  PtrInfStr<Ptr<_Value_ptr_type>, _Rank - 1>::value value;
	};


	/**
	 * \brief value = value type
	 * \tparam _Value_ptr_type value type
	 */
	template< typename _Value_ptr_type>
	struct PtrInfStr<_Value_ptr_type, NULL>
	{
		typedef _Value_ptr_type value;
	};

	/**
	 * \brief returns a given number of pointers to pointers of type
	 * \brief âîçâðàùàåò çàäàííîå êîëè÷åñòâî óêàçàòåëåé íà óêàçàòåëè òèïà
	 * \tparam _Value_ptr_type value type
	 * \tparam _Rank rank
	 */
	template<typename _Value_ptr_type, rank_t _Rank>
	using PtrInf = typename PtrInfStr<_Value_ptr_type, _Rank>::value;


	/**
	 * \brief init pointer-type
	 * \tparam _Value_ptr_type value type
	 * \tparam _Rank rank
	 * \tparam _Size size
	 */
	template<typename _Value_ptr_type, rank_t _Rank, rank_t _Size>
	using PtrInfInit = typename PtrInfStr<_Value_ptr_type, _Rank - 1>::value[_Size];

	/**
	 * \brief return _Value_ptr_type*
	 * \tparam _Value_ptr_type value type
	 */
	template<typename _Value_ptr_type>
	using Ptr1 = typename PtrInfStr<_Value_ptr_type, 1>::value;

	/**
	 * \brief return _Value_ptr_type**
	 * \tparam _Value_ptr_type value type
	 */
	template<typename _Value_ptr_type>
	using Ptr2 = typename PtrInfStr<_Value_ptr_type, 2>::value;

	/**
	 * \brief return _Value_ptr_type***
	 * \tparam _Value_ptr_type value type
	 */
	template<typename _Value_ptr_type>
	using Ptr3 = typename PtrInfStr<_Value_ptr_type, 3>::value;

	//////////////////////////////////////////////////////////////////////////////

	///---
	template<typename _Value_getting_type, rank_t... _Einf>
	struct ArrayGetElement
	{};

	/**
	 * \brief Fast getting element from array / áûñòðîå ïîëó÷åíèå ýëåìåíòà èç ìàññèâà
	 * \tparam _Value_getting_type type of element / òèï ýëåìåíòà
	 * \tparam _E0 first array coordinate / ïåðâàÿ êîîðäèíàòà ìàññèâà
	 * \tparam _Einf array coordinates / îñòàëüíûå êîîðäèíàòû ìàññèâà
	 */
	template<typename _Value_getting_type, rank_t _E0, rank_t... _Einf>
	struct ArrayGetElement<_Value_getting_type, _E0, _Einf...>
	{
		/**
		 * \brief get an element in your array / ïîëó÷èòü ýëåìåíò â âàøåì ìàññèâå
		 * \param _Data your array / âàø ìàññèâ
		 * \return element of array/ ýëåìåíò ìàññèâà
		 */
		static constexpr inline _Value_getting_type& (at) \
			(Ref<PtrInf<_Value_getting_type, argsum(_Einf...) + 1>> _Data)
		{
			return ArrayGetElement<_Value_getting_type, _Einf...>::at(_Data[_E0]);
		}
	};

	/**
	 * \brief Fast getting element from array / áûñòðîå ïîëó÷åíèå ýëåìåíòà èç ìàññèâà
	 * \tparam _Value_getting_type type of element / òèï ýëåìåíòà
	 * \tparam _E0 first array coordinate / ïåðâàÿ êîîðäèíàòà ìàññèâà
	 */
	template<typename _Value_getting_type, rank_t _E0>
	struct ArrayGetElement<_Value_getting_type, _E0>
	{
		/**
		 * \brief get an element in your array / ïîëó÷èòü ýëåìåíò â âàøåì ìàññèâå
		 * \param _Data your array / âàø ìàññèâ
		 * \return element of array/ ýëåìåíò ìàññèâà
		 */
		static constexpr inline _Value_getting_type& (at) \
			(Ref<PtrInf<_Value_getting_type, 1>> _Data)
		{
			return _Data[_E0];
		}
	};



	//////////////////////////////////////////////////////////////////////////////

	///---
	template<typename _Value_getting_type, rank_t... _Einf>
	struct ArrayFill {};

	/**
	 * \brief filling your array | coping your array in your pointer-array
	 * \brief çàïîëíåíèå âàøåãî ìàññèâà | êîïèðîâàíèå âàøåãî ìàññèâà â âàø ìàññèâ óêàçàòåëåé
	 * \tparam _Value_type value type of array / òèï çíà÷åíèé ìàññèâà
	 * \tparam _Size_0 first size of array / ðàçìåð ïåðâîãî ðàíãà(èçìåðåíèÿ)
	 * \tparam _Size_inf sizes of array / ðàçìåðû ðàíãîâ(èçìåðåíèé)
	 */
	template<typename _Value_type, rank_t _Size_0, rank_t... _Size_inf>
	struct ArrayFill<_Value_type, _Size_0, _Size_inf...>
	{
		/**
		 * \brief filling your array
		 * \brief çàïîëíåíèå âàøåãî ìàññèâà
		 * \param _Data your array / âàø ìàññèâ
		 */
		static constexpr inline void(fill) \
			(Ref<PtrInf<_Value_type, argsum(_Size_inf...) + 1>> _Data)
		{
			if constexpr (!(_Size_0 > 0))
			{
				static_assert(true, "first size less then 0");
			}

			for (rank_t i = 0; i < _Size_0; i++)
			{
				_Data[i] = new PtrInf<_Value_type, argsum(_Size_inf...) - 1>[_Size_0];
				ArrayFill<_Value_type, _Size_inf...>::fill(_Data[i]);
			}
		}

		/**
		 * \brief coping your array in your pointer-array;
		 * utility function
		 * \brief êîïèðîâàíèå âàøåãî ìàññèâà â âàø ìàññèâ óêàçàòåëåé;
		 * ñëóæåáíàÿ ôóíêöèÿ
		 * \param _Data your array / âàø ìàññèâ
		 * \param _Data_copy your pointer-array / âàø ìàññèâ óêàçàòåëåé
		 * \param iter èòåðàòîð
		 */
		static constexpr inline void(fill) \
			(Ref<PtrInf<Ptr<_Value_type>, argsum(_Size_inf...) + 1>> _Data, \
				Ref<PtrInf<_Value_type, 1>> _Data_copy, Ref<rank_t> iter)
		{
			for (rank_t i = 0; i < _Size_0; i++)
			{
				_Data[i] = new PtrInf<_Value_type, argsum(_Size_inf...)>[_Size_0];
				ArrayFill<_Value_type, _Size_inf...>::fill(_Data[i], _Data_copy, iter);
			}
		}

		/**
		 * \brief coping your array in your pointer-array
		 * \brief êîïèðîâàíèå âàøåãî ìàññèâà â âàø ìàññèâ óêàçàòåëåé
		 * \param _Data your array / âàø ìàññèâ
		 * \param _Data_copy your pointer-array / âàø ìàññèâ óêàçàòåëåé
		 */
		static constexpr inline void(fill) \
			(Ref<PtrInf<Ptr<_Value_type>, argsum(_Size_inf...) + 1>> _Data, \
				Ref<PtrInf<_Value_type, 1>> _Data_copy)
		{
			rank_t iter(0);
			fill(_Data, _Data_copy, iter);
		}

		/**
		 * \brief rank of array
		 * \brief ðàíã èëè æå êîëè÷åñòâî èçìåðåíèé ìàññèâà
		 */
		rank_t rank = argsum(_Size_inf...);

		/**
		 * \brief this type
		 * \brief äàííûé òèï
		 */
		typedef typename PtrInf<_Value_type, argsum(_Size_inf...) + 1> type;

		/**
		 * \brief this type-pointer
		 * \brief äàííûé òèï-óêàçàòåëü
		 */
		typedef typename PtrInf< Ptr<_Value_type>, argsum(_Size_inf...) + 1> type_ptr;

		/**
		 * \brie this type
		 * \brie äàííûé òèï äëÿ èíèöèàëèçàöèè
		 */
		typedef typename PtrInf<_Value_type, argsum(_Size_inf...)> \
			type_init[variadic_arg_last<rank_t, _Size_inf...>::value];

		/**
		 * \brief this pointer-type
		 * \briefäàííûé òèï-óêàçàòåëü äëÿ èíèöèàëèçàöèè
		 */
		typedef typename PtrInf<Ptr<_Value_type>, argsum(_Size_inf...)> \
			type_init_ptr[variadic_arg_last<rank_t, _Size_inf...>::value];
	};

	/**
	 * \brief filling your array | coping your array in your pointer-array
	 * \brief çàïîëíåíèå âàøåãî ìàññèâà | êîïèðîâàíèå âàøåãî ìàññèâà â âàø ìàññèâ óêàçàòåëåé
	 * \tparam _Value_type value type of array / òèï çíà÷åíèé ìàññèâà
	 * \tparam _Size_0 first size of array / ðàçìåð ïåðâîãî ðàíãà(èçìåðåíèÿ)
	 */
	template<typename _Value_type, rank_t _Size_0>
	struct ArrayFill<_Value_type, _Size_0>
	{
		/**
		 * \brief filling your array
		 * \brief çàïîëíåíèå âàøåãî ìàññèâà
		 * \param _Data your array / âàø ìàññèâ
		 */
		static constexpr inline void(fill) \
			(Ref<PtrInf<_Value_type, 1>> _Data)
		{
			for (rank_t i = 0; i < _Size_0; i++)
			{
				_Data[i] = _Value_type{};

			}
		}

		/**
		 * \brief coping your array in your pointer-array;
		 * utility function
		 * \brief êîïèðîâàíèå âàøåãî ìàññèâà â âàø ìàññèâ óêàçàòåëåé;
		 * ñëóæåáíàÿ ôóíêöèÿ
		 * \param _Data your array / âàø ìàññèâ
		 * \param _Data_copy your pointer-array / âàø ìàññèâ óêàçàòåëåé
		 * \param iter èòåðàòîð
		 */
		static constexpr inline void(fill) \
			(Ref<PtrInf<Ptr<_Value_type>, 1>> _Data, \
				Ref<PtrInf<_Value_type, 1>> _Data_copy, Ref<rank_t> iter)
		{
			for (rank_t i = 0; i < _Size_0; i++)
			{
				_Data[i] = &_Data_copy[iter];
				iter++;

			}
		}

		/**
		 * \brief coping your array in your pointer-array
		 * \brief êîïèðîâàíèå âàøåãî ìàññèâà â âàø ìàññèâ óêàçàòåëåé
		 * \param _Data your array / âàø ìàññèâ
		 * \param _Data_copy your pointer-array / âàø ìàññèâ óêàçàòåëåé
		 */
		static constexpr inline void(fill) \
			(Ref<PtrInf<Ptr<_Value_type>, 1>> _Data, Ref<PtrInf<_Value_type, 1>> _Data_copy)
		{
			rank_t _Iter(0);
			fill(_Data, _Data_copy, _Iter);
		}

		/**
		 * \brief rank of array
		 * \brief ðàíã èëè æå êîëè÷åñòâî èçìåðåíèé ìàññèâà
		 */
		rank_t rank = 1;

		/**
		 * \brief this type
		 * \brief äàííûé òèï
		 */
		typedef typename PtrInf<_Value_type, 1> type;

		/**
		 * \brief this type-pointer
		 * \brief äàííûé òèï-óêàçàòåëü
		 */
		typedef typename PtrInf<Ptr<_Value_type>, 1> type_ptr;

		/**
		 * \brie this type
		 * \brie äàííûé òèï äëÿ èíèöèàëèçàöèè
		 */
		typedef typename PtrInf<_Value_type, 0> type_init[_Size_0];

		/**
		 * \brief this pointer-type
		 * \briefäàííûé òèï-óêàçàòåëü äëÿ èíèöèàëèçàöèè
		 */
		typedef typename PtrInf<Ptr<_Value_type>, 0> type_init_ptr[_Size_0];
	};

	//////////////////////////////////////////////////////////////////////////////

	template<typename _Value_type, rank_t _Size = 1>
	inline _Value_type fix_array[_Size] = {};

	//////////////////////////////////////////////////////////////////////////////


	//////////////////////////////////////////////////////////////////////////////

	template<typename _Value_type, rank_t _Rank>
	class Data
	{
	public:

		/**
		 * \brief Implementing a multidimensional array over a one-dimensional array
		 * \brief Îñóùåñòâëåíèå ìíîãîìåðíîãî ìàññèâà íàä îäíîìåðíûì ìàññèâîì
		 * \tparam _Sizes Each rank size
		 * / Ðàçìåðû êàæäîãî ðàíãà (èçìåðåíèÿ)
		 */
		template<rank_t... _Sizes>
		class DataImpl
		{
		public:

			/**
			 * \brief Multidimensional array with pointers to one-dimensional array
			 * \brief Ìíîãîìåðíûé ìàññèâ ñ óêàçàòåëÿìè íà îäíîìåðíûé ìàññèâ
			 */
			PtrInf<Ptr<_Value_type>, _Rank> data_ptr;

			/**
			 * \brief
			 * \param Data_src The one-dimensional array on which the implementation is taking place
			 * / Îäíîìåðíûé ìàññèâ, íàä êîòîðûì ïðîèçîéä¸ò îñóùåñòâëåíèå
			 */

			DataImpl() :
				data_ptr(new PtrInf<_Value_type, _Rank>[variadic_func_arg_last(_Sizes...)])
			{

			}

			explicit DataImpl(Ptr<_Value_type> Data_src) :
				data_ptr(new PtrInf<_Value_type, _Rank>[variadic_func_arg_last(_Sizes...)])
			{
				ArrayFill<_Value_type, _Sizes...>::fill(data_ptr, Data_src);
			}

			constexpr inline void fill_at(Ptr<_Value_type> Data_src)
			{
				ArrayFill<_Value_type, _Sizes...>::fill(data_ptr, Data_src);
			}

			PtrInf<Ptr<_Value_type>, _Rank - 1> operator [] (const rank_t At_rank_t)
			{
				return data_ptr[At_rank_t];
			}

		};

		//////////////////////////////////////////////////////////////////////////////

		static inline rank_t dimension = _Rank;
		static inline rank_t rank = _Rank;

		//////////////////////////////////////////////////////////////////////////////

		template<rank_t _Size0, rank_t... _Sizes>
		class DataImpl2
		{
		public:
			DataImpl2<_Sizes...> tuple;
		};

		template<rank_t _Size0>
		class DataImpl2<_Size0>
		{
		public:
			PtrInf<Ptr<_Value_type>, _Rank> data_ptr;
			constexpr inline  _Value_type& (at)(rank_t idx)
			{
				return *data_ptr[idx];
			}
		};
	};

	//////////////////////////////////////////////////////////////////////////////

	template<typename _Type0, typename... _Types>
	struct PairInf
	{
		typedef _Type0 type;
		typedef PairInf<_Types...> next_pair_type;
		_Type0 value_of_type = {};
		PairInf<_Types...> next_pair;
	};

	template<typename _Type0>
	struct PairInf<_Type0>
	{
		typedef _Type0 type;
		_Type0 value_of_type = {};
	};

	//////////////////////////////////////////////////////////////////////////////

}; // namespace tu

template<typename _Value_type>
constexpr inline std::vector<_Value_type>& operator <<
(std::vector<_Value_type>& vector_first, std::vector<_Value_type>& vector_second)
{
	for (_Value_type& element : vector_second)
	{
		vector_first.push_back(element);
	}
	return vector_first;
}

#define TU_CREATE_FILLED_ARRAY(_Value_type, _Size_0, _Name) \
	tu::ArrayFill<_Value_type, _Size_0>::type _Name = \
	new tu::ArrayFill<_Value_type, _Size_0>::type_init
