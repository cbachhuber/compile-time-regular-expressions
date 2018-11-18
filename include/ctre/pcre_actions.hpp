#ifndef CTRE__PCRE_ACTIONS__HPP
#define CTRE__PCRE_ACTIONS__HPP

#include "pcre.hpp"
#include "atoms.hpp"
#include "atoms_characters.hpp"
#include "id.hpp"
#include <cstdint>
#include <limits>

namespace ctre {
	
template <size_t Counter> struct pcre_parameters {
	static constexpr size_t current_counter = Counter;
};

#if __cpp_deduction_guides
template <typename Stack = ctll::list<>, typename Parameters = pcre_parameters<0>> struct pcre_context {
constexpr pcre_context() noexcept { }
constexpr pcre_context(Stack, Parameters) noexcept { }
#else
template <typename Stack = ctll::list<>, typename Parameters = pcre_parameters<0>> struct pcre_context_t {
constexpr pcre_context_t() noexcept { }
#endif
	using stack_type = Stack;
	using parameters_type = Parameters;
	static constexpr inline auto stack = stack_type();
	static constexpr inline auto parameters = parameters_type();
	
};


#if __cpp_deduction_guides

template <typename Stack = ctll::list<>, typename Parameters = pcre_parameters<0>> using pcre_context_t = pcre_context<Stack, Parameters>;

template <typename... Content, typename Parameters> pcre_context(ctll::list<Content...>, Parameters) -> pcre_context<ctll::list<Content...>, Parameters>;
#else

// simulation of C++17 CTAD with function call

template <typename... Content, typename Parameters> constexpr auto pcre_context(ctll::list<Content...>, Parameters) -> pcre_context_t<ctll::list<Content...>, Parameters> { return {}; };
#endif
	
template <size_t Value> struct number { };

template <size_t Id> struct capture_id { };
	
struct pcre_actions {
// i know it's ugly, but it's more readable
#include "actions/characters.inc.hpp"
#include "actions/sequence.inc.hpp"
#include "actions/hexdec.inc.hpp"
#include "actions/options.inc.hpp"
#include "actions/class.inc.hpp"
#include "actions/repeat.inc.hpp"
#include "actions/named_class.inc.hpp"
#include "actions/set.inc.hpp"
#include "actions/asserts.inc.hpp"
#include "actions/capture.inc.hpp"
#include "actions/backreference.inc.hpp"
};


}

#endif
