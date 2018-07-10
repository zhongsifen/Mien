#pragma once

#include "core_abstract.h"
#include "../cuda/tensor.h"
#include <iterator>
#include <memory>
#include <sstream>
#include <type_traits>
#include "../statistics.h"
#include "../rand.h"
#include "../algs.h"
#include <utility>
#include <tuple>
#include <cmath>
#include <vector>
#include "../cuda/tensor_tools.h"
#include <type_traits>
#include "../metaprogramming.h"

#ifdef _MSC_VER
// Tell Visual Studio not to recursively inline functions very much because otherwise it
// takes hours to compile the DNN code sometimes.  It's crazy.  Hopefully we can remove
// this some day when the visual studio compiler is more efficient.
#pragma inline_depth(2)
#endif

using namespace dlib;

namespace dlib {

class add_loss_layer
{
	template <typename T, typename enabled = void>
	struct get_loss_layer_training_label_type
	{
		typedef no_label_type type;
	};
	template <typename T>
	struct get_loss_layer_training_label_type<T, typename std::enable_if<sizeof(typename T::training_label_type) != 0>::type>
	{
		typedef typename T::training_label_type type;
	};

	template <typename T, typename enabled = void>
	struct get_loss_layer_output_label_type
	{
		typedef no_label_type type;
	};
	template <typename T>
	struct get_loss_layer_output_label_type<T, typename std::enable_if<sizeof(typename T::output_label_type) != 0>::type>
	{
		typedef typename T::output_label_type type;
	};

public:
	typedef LOSS_DETAILS loss_details_type;
	typedef SUBNET subnet_type;
	typedef typename subnet_type::input_type input_type;
	const static size_t num_layers = subnet_type::num_layers + 1;
	// Note that the loss layer doesn't count as an additional computational layer.
	const static size_t num_computational_layers = subnet_type::num_computational_layers;
	typedef typename get_loss_layer_training_label_type<LOSS_DETAILS>::type training_label_type;
	typedef typename get_loss_layer_output_label_type<LOSS_DETAILS>::type output_label_type;

	static_assert(is_nonloss_layer_type<SUBNET>::value,
		"SUBNET must be of type add_layer, add_skip_layer, or add_tag_layer.");


	add_loss_layer() {};
	add_loss_layer(const add_loss_layer&) = default;
	add_loss_layer& operator=(const add_loss_layer&) = default;
	add_loss_layer(add_loss_layer&& item) : add_loss_layer() { swap(item); }
	add_loss_layer& operator=(add_loss_layer&& item) { swap(item); return *this; }

	template <typename T, typename U>
	add_loss_layer(
		const add_loss_layer<T, U>& item
	) :
		loss(item.loss_details()),
		subnetwork(item.subnet())
	{}

	template <typename ...T>
	add_loss_layer(
		const LOSS_DETAILS& layer_det,
		T&& ...args
	) :
		loss(layer_det),
		subnetwork(std::forward<T>(args)...)
	{
	}

	template <typename ...T>
	add_loss_layer(
		LOSS_DETAILS&& layer_det,
		T&& ...args
	) :
		loss(std::move(layer_det)),
		subnetwork(std::forward<T>(args)...)
	{
	}

	template <typename T, typename ...U>
	struct disable_forwarding_constr
	{
		const static bool value = std::is_constructible<LOSS_DETAILS, T>::value;
	};
	template <typename ...T>
	struct disable_forwarding_constr<add_loss_layer<T...>>
	{
		const static bool value = true;
	};

	template <
		typename ...T,
		typename = typename std::enable_if<!disable_forwarding_constr<typename std::remove_reference<T>::type...>::value>::type
	>
		add_loss_layer(
			T&& ...args
		) :
		subnetwork(std::forward<T>(args)...)
	{
	}

	template <typename forward_iterator>
	void to_tensor(
		forward_iterator ibegin,
		forward_iterator iend,
		resizable_tensor& data
	) const
	{
		subnetwork.to_tensor(ibegin, iend, data);
	}

	unsigned int sample_expansion_factor() const { return subnet().sample_expansion_factor(); }

	template <typename output_iterator>
	void operator() (
		const tensor& x,
		output_iterator obegin
		)
	{
		subnetwork.forward(x);
		const dimpl::subnet_wrapper<subnet_type> wsub(subnetwork);
		loss.to_label(x, wsub, obegin);
	}

	template <typename forward_iterator, typename output_iterator>
	void operator() (
		forward_iterator ibegin,
		forward_iterator iend,
		output_iterator obegin
		)
	{
		to_tensor(ibegin, iend, temp_tensor);
		(*this)(temp_tensor, obegin);
	}

	const output_label_type& operator() (const input_type& x)
	{
		(*this)(&x, &x + 1, &temp_label);
		return temp_label;
	}

	template <typename ...T>
	const output_label_type& process(const input_type& x, T&& ...args)
	{
		to_tensor(&x, &x + 1, temp_tensor);
		subnetwork.forward(temp_tensor);
		const dimpl::subnet_wrapper<subnet_type> wsub(subnetwork);
		loss.to_label(temp_tensor, wsub, &temp_label, std::forward<T>(args)...);
		return temp_label;
	}

	template <typename iterable_type, typename ...T>
	std::vector<output_label_type> process_batch(const iterable_type& data, size_t batch_size, T&& ...args)
	{
		std::vector<output_label_type> results(std::distance(data.begin(), data.end()));
		auto o = results.begin();
		auto i = data.begin();
		auto num_remaining = results.size();
		while (num_remaining != 0)
		{
			auto inc = std::min(batch_size, num_remaining);
			to_tensor(i, i + inc, temp_tensor);
			subnetwork.forward(temp_tensor);
			const dimpl::subnet_wrapper<subnet_type> wsub(subnetwork);
			loss.to_label(temp_tensor, wsub, o, std::forward<T>(args)...);

			i += inc;
			o += inc;
			num_remaining -= inc;
		}
		return results;
	}

	template <typename iterable_type>
	std::vector<output_label_type> operator() (
		const iterable_type& data,
		size_t batch_size = 128
		)
	{
		std::vector<output_label_type> results(std::distance(data.begin(), data.end()));
		auto o = results.begin();
		auto i = data.begin();
		auto num_remaining = results.size();
		while (num_remaining != 0)
		{
			auto inc = std::min(batch_size, num_remaining);
			(*this)(i, i + inc, o);
			i += inc;
			o += inc;
			num_remaining -= inc;
		}
		return results;
	}

	template <typename label_iterator>
	double compute_loss(
		const tensor& x,
		label_iterator lbegin
	)
	{
		subnetwork.forward(x);
		dimpl::subnet_wrapper<subnet_type> wsub(subnetwork);
		return loss.compute_loss_value_and_gradient(x, lbegin, wsub);
	}

	template <typename forward_iterator, typename label_iterator>
	double compute_loss(
		forward_iterator ibegin,
		forward_iterator iend,
		label_iterator lbegin
	)
	{
		to_tensor(ibegin, iend, temp_tensor);
		return compute_loss(temp_tensor, lbegin);
	}

	double compute_loss(
		const tensor& x
	)
	{
		subnetwork.forward(x);
		dimpl::subnet_wrapper<subnet_type> wsub(subnetwork);
		return loss.compute_loss_value_and_gradient(x, wsub);
	}

	template <typename forward_iterator>
	double compute_loss(
		forward_iterator ibegin,
		forward_iterator iend
	)
	{
		to_tensor(ibegin, iend, temp_tensor);
		return compute_loss(temp_tensor);
	}

	template <typename label_iterator>
	double compute_parameter_gradients(
		const tensor& x,
		label_iterator lbegin
	)
	{
		subnetwork.forward(x);
		dimpl::subnet_wrapper<subnet_type> wsub(subnetwork);
		double l = loss.compute_loss_value_and_gradient(x, lbegin, wsub);
		subnetwork.back_propagate_error(x);
		return l;
	}
	template <typename forward_iterator, typename label_iterator>
	double compute_parameter_gradients(
		forward_iterator ibegin,
		forward_iterator iend,
		label_iterator lbegin
	)
	{
		to_tensor(ibegin, iend, temp_tensor);
		return compute_parameter_gradients(temp_tensor, lbegin);
	}
	double compute_parameter_gradients(
		const tensor& x
	)
	{
		subnetwork.forward(x);
		dimpl::subnet_wrapper<subnet_type> wsub(subnetwork);
		double l = loss.compute_loss_value_and_gradient(x, wsub);
		subnetwork.back_propagate_error(x);
		return l;
	}
	template <typename forward_iterator>
	double compute_parameter_gradients(
		forward_iterator ibegin,
		forward_iterator iend
	)
	{
		to_tensor(ibegin, iend, temp_tensor);
		return compute_parameter_gradients(temp_tensor);
	}

	template <typename solver_type>
	void update_parameters(
		sstack<solver_type> solvers,
		double learning_rate
	)
	{
		subnetwork.update_parameters(solvers, learning_rate);
	}

	const subnet_type& subnet() const { return subnetwork; }
	subnet_type& subnet() { return subnetwork; }
	const loss_details_type& loss_details() const { return loss; }
	loss_details_type& loss_details() { return loss; }

	void clean(
	)
	{
		temp_tensor.clear();
		subnetwork.clean();
	}

	template <typename T, typename U>
	friend void serialize(const add_loss_layer<T, U>& item, std::ostream& out);
	template <typename T, typename U>
	friend void deserialize(add_loss_layer<T, U>& item, std::istream& in);

	friend std::ostream& operator<< (std::ostream& out, const add_loss_layer& item)
	{
		int min_length = 0;
		item.print(out, 0, min_length);
		return out;
	}

	void print(std::ostream& out, unsigned long idx, int& min_length) const
	{
		out << "layer<" << idx << ">\t" << loss_details() << "\n";
		subnet().print(out, idx + 1, min_length);
	}

private:


	void swap(add_loss_layer& item)
	{
		std::swap(loss, item.loss);
		std::swap(subnetwork, item.subnetwork);
	}

	loss_details_type loss;
	subnet_type subnetwork;

	// These two objects don't logically contribute to the state of this object.  They
	// are here to prevent them from being reallocated over and over.
	output_label_type temp_label;
	resizable_tensor temp_tensor;
};

}
