// Copyright 2017 The Abseil Authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// Copyright 2017 The Abseil Authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// File: flags.cpp - Type-safe enum-based bitfields
//

#include <zeus/flags.h>

/**
 * \file base/flags.h
 * \brief Enum-based bit fields
 */

namespace zeus {

/**
 * \class Flags
 * \brief Type-safe container for enum-based bitfields
 *
 * The Flags template class provides type-safe bitwise operators on enum values.
 * It allows using enum types for bitfields, while preventing unsafe casts from
 * integer types and mixing of flags from different enum types.
 *
 * To use the Flags class, declare an enum containing the desired bit flags, and
 * use the Flags<enum> class to store bitfields based on the enum. If bitwise
 * operators on the underlying enum are also desired, they can be enabled with
 * the ZEUS_FLAGS_ENABLE_OPERATORS(enum) macro.
 */

/**
 * \typedef Flags::Type
 * \brief The underlying data type of the enum
 */

/**
 * \fn Flags::Flags()
 * \brief Construct a Flags instance with a zero value
 */

/**
 * \fn Flags::Flags(E flag)
 * \brief Construct a Flags instance storing the \a flag
 * \param[in] flag The initial value
 */

/**
 * \fn Flags &Flags::operator&=(E flag)
 * \brief Store the bitwise AND of this Flags and the \a flag in this Flags
 * \param[in] flag The second operand
 * \return A reference to this Flags
 */

/**
 * \fn Flags &Flags::operator&=(Flags other)
 * \brief Store the bitwise AND of this Flags and the \a other Flags in this Flags
 * \param[in] other The second operand
 * \return A reference to this Flags
 */

/**
 * \fn Flags &Flags::operator|=(E flag)
 * \brief Store the bitwise OR of this Flags and the \a flag in this Flags
 * \param[in] flag The second operand
 * \return A reference to this Flags
 */

/**
 * \fn Flags &Flags::operator|=(Flags other)
 * \brief Store the bitwise OR of this Flags and the \a other Flags in this Flags
 * \param[in] other The second operand
 * \return A reference to this Flags
 */

/**
 * \fn Flags &Flags::operator^=(E flag)
 * \brief Store the bitwise XOR of this Flags and the \a flag in this Flags
 * \param[in] flag The second operand
 * \return A reference to this Flags
 */

/**
 * \fn Flags &Flags::operator^=(Flags other)
 * \brief Store the bitwise XOR of this Flags and the \a other Flags in this Flags
 * \param[in] other The second operand
 * \return A reference to this Flags
 */

/**
 * \fn bool Flags::operator==(E flag)
 * \brief Compare flags for equality
 * \param[in] flag The second operand
 * \return True if the Flags and \a flag are equal, false otherwise
 */

/**
 * \fn bool Flags::operator==(Flags other)
 * \brief Compare flags for equality
 * \param[in] other The second operand
 * \return True if the Flags and \a other are equal, false otherwise
 */

/**
 * \fn bool Flags::operator!=(E flag)
 * \brief Compare flags for non-equality
 * \param[in] flag The second operand
 * \return True if the Flags and \a flag are not equal, false otherwise
 */

/**
 * \fn bool Flags::operator!=(Flags other)
 * \brief Compare flags for non-equality
 * \param[in] other The second operand
 * \return True if the Flags and \a other are not equal, false otherwise
 */

/**
 * \fn Flags::operator Type() const
 * \brief Convert the Flags to the underlying integer type
 * \return The Flags value as an integer
 */

/**
 * \fn Flags::operator bool() const
 * \brief Convert the Flags to a boolean
 * \return True if at least one flag is set, false otherwise
 */

/**
 * \fn Flags Flags::operator&(E flag) const
 * \brief Compute the bitwise AND of this Flags and the \a flag
 * \param[in] flag The second operand
 * \return A Flags containing the result of the AND operation
 */

/**
 * \fn Flags Flags::operator&(Flags other) const
 * \brief Compute the bitwise AND of this Flags and the \a other Flags
 * \param[in] other The second operand
 * \return A Flags containing the result of the AND operation
 */

/**
 * \fn Flags Flags::operator|(E flag) const
 * \brief Compute the bitwise OR of this Flags and the \a flag
 * \param[in] flag The second operand
 * \return A Flags containing the result of the OR operation
 */

/**
 * \fn Flags Flags::operator|(Flags other) const
 * \brief Compute the bitwise OR of this Flags and the \a other Flags
 * \param[in] other The second operand
 * \return A Flags containing the result of the OR operation
 */

/**
 * \fn Flags Flags::operator^(E flag) const
 * \brief Compute the bitwise XOR of this Flags and the \a flag
 * \param[in] flag The second operand
 * \return A Flags containing the result of the XOR operation
 */

/**
 * \fn Flags Flags::operator^(Flags other) const
 * \brief Compute the bitwise XOR of this Flags and the \a other Flags
 * \param[in] other The second operand
 * \return A Flags containing the result of the XOR operation
 */

/**
 * \fn Flags Flags::operator~() const
 * \brief Compute the bitwise NOT of this Flags
 * \return A Flags containing the result of the NOT operation
 */

/**
 * \fn bool Flags::operator!() const
 * \brief Check if flags are set
 * \return True if no flags is set, false otherwise
 */

/**
 * \def ZEUS_FLAGS_ENABLE_OPERATORS(enum)
 * \brief Enable bitwise operations on the \a enum enumeration
 *
 * This macro enables the bitwise AND, OR, XOR and NOT operators on the given
 * \a enum. This allows the enum values to be safely used in bitwise operations
 * with the Flags<> class.
 */

} /* namespace zeus */
