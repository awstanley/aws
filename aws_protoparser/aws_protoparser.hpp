/* This file is part of Alex's Coding Tools ('aws').
 * http://github.com/awstanley/aws/
 *
 * Released into the public domain.
 *//**
 *
 * @file aws_protoparser.hpp
 * @version 1.1.0
 * @date 2015-07-20
 * @since 2011-11-15
 * @licence Public Domain
 *
 * This file is used to parse data from the command line/terminal
 * or other strings based on a protocol buffer definition (.proto).
 *
 *  Version History
 *    1.1.0
 *      2015-07-20
 *         Rewrite and overhaul to pure header.
 *         Major bug fixes and overhaul to support more than the bare minimum.
 *         Moving to C++11 functions (std's stod, stof, etc.).
 *         Added nested message support.
 *         Moved to 'aws' namespace; added protocolparser namespace.
 *         (Preparing for) initial release to github.
 *
 *    1.0.x
 *         Various changes without version bumps (internal only).
 *         (Impacted project codenames: alp, cpt, alps, l3 (lll), xlp, xlc, xpl)
 *
 *    1.0.0
 *       2011-11-15
 *          Initial code release to limited projects.
 */

#ifndef _AWS_PROTOPARSER_HPP_
#define _AWS_PROTOPARSER_HPP_

// Protocol Buffers includes.
#include <google/protobuf/message.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/generated_enum_reflection.h>
#include <google/protobuf/unknown_field_set.h>

// String functionality, as C++ is already needed
// it's better to keep things sane.
#include <string>

// std::transform
#include <algorithm>

// std::stringstream
#include <sstream>

// stdint (u)intX_t
#include <stdint.h>

// std::vector
#include <vector>

// Helpers to keep the code sane and to make maintaining this less painful
// should anything change.
#define MESSAGE ::google::protobuf::Message
#define DESCRIPTOR ::google::protobuf::Descriptor
#define REFLECTION ::google::protobuf::Reflection
#define FIELDDESC ::google::protobuf::FieldDescriptor

namespace aws {
	namespace protocolparser {

		// Forward
		inline std::string Dump(MESSAGE *msg, int indent);

#pragma region Boolean
		/**
		* @brief Sets the value of a field (boolean)
		* @in msg Protobuf Message object
		* @in field_name Name of field (as string).
		* @in value Value to be set.
		* @return True if successful; false otherwise.
		*
		* Failure should typically only be because the field is missing.
		*/
		inline bool SetBoolean(MESSAGE *msg, std::string field_name, bool value) {
			bool rv = false;
			const DESCRIPTOR *desc = msg->GetDescriptor();
			const REFLECTION *refl = msg->GetReflection();
			const FIELDDESC *field = desc->FindFieldByName(field_name);

			if (field != nullptr) {
				if (field->type() == FIELDDESC::TYPE_BOOL) {
					refl->SetBool(msg, field, value);
					rv = true;
				}
			}
			return rv;
		}

		/**
		* @brief Gets the value of a field (boolean).
		* @in msg Protobuf Message object
		* @in field_name Name of field (as string).
		* @in default_value Default value (default false)
		* @in set_if_missing If true it will attempt to set the field if the value is uninitialised.
		* @return Value of the field (or default_value if missing).
		*/
		inline bool GetBoolean(MESSAGE *msg, std::string field_name,
			bool default_value = false, bool set_if_missing = false) {

			bool out = false;

			const DESCRIPTOR *desc = msg->GetDescriptor();
			const REFLECTION *refl = msg->GetReflection();
			const FIELDDESC *field = desc->FindFieldByName(field_name);

			if (field != nullptr) {
				if (field->type() == FIELDDESC::TYPE_BOOL) {
					out = refl->GetBool(*msg, field);
					if (out == false && set_if_missing) {
						refl->SetBool(msg, field, default_value);
						out = default_value;
					}
				}
			}
			return out;
		}
#pragma endregion
#pragma region Float
		/**
		 * @brief Sets the value of a field (float)
		 * @in msg Protobuf Message object
		 * @in field_name Name of field (as string).
		 * @in value Value to be set.
		 * @return True if successful; false otherwise.
		 *
		 * Failure should typically only be because the field is missing.
		 */
		inline bool SetFloat(MESSAGE *msg, std::string field_name, float value) {
			bool rv = false;
			const DESCRIPTOR *desc = msg->GetDescriptor();
			const REFLECTION *refl = msg->GetReflection();
			const FIELDDESC *field = desc->FindFieldByName(field_name);

			if (field != nullptr) {
				if (field->type() == FIELDDESC::TYPE_FLOAT) {
					refl->SetFloat(msg, field, value);
					rv = true;
				}
			}
			return rv;
		}

		/**
		 * @brief Gets the value of a field (float).
		 * @in msg Protobuf Message object
		 * @in field_name Name of field (as string).
		 * @in default_value Default value (default 0.0f)
		 * @in set_if_missing If true it will attempt to set the field if the value is uninitialised.
		 * @return Value of the field (or default_value if missing).
		 */
		inline float GetFloat(MESSAGE *msg, std::string field_name,
			float default_value = 0.0f, bool set_if_missing=false) {

			float out = 0.0f;

			const DESCRIPTOR *desc = msg->GetDescriptor();
			const REFLECTION *refl = msg->GetReflection();
			const FIELDDESC *field = desc->FindFieldByName(field_name);

			if (field != nullptr) {
				if (field->type() == FIELDDESC::TYPE_FLOAT) {
					out = refl->GetFloat(*msg, field);
					if (out == 0.0f && set_if_missing) {
						refl->SetFloat(msg, field, default_value);
						out = default_value;
					}
				}
			}
			return out;
		}
#pragma endregion
#pragma region Double
		/**
		 * @brief Sets the value of a field (double)
		 * @in msg Protobuf Message object
		 * @in field_name Name of field (as string).
		 * @in value Value to be set.
		 * @return True if successful; false otherwise.
		 *
		 * Failure should typically only be because the field is missing.
		 */
		inline bool SetDouble(MESSAGE *msg, std::string field_name, float value) {
			bool rv = false;
			const DESCRIPTOR *desc = msg->GetDescriptor();
			const REFLECTION *refl = msg->GetReflection();
			const FIELDDESC *field = desc->FindFieldByName(field_name);

			if (field != nullptr) {
				if (field->type() == FIELDDESC::TYPE_DOUBLE) {
					refl->SetDouble(msg, field, value);
					rv = true;
				}
			}
			return rv;
		}

		/**
		 * @brief Gets the value of a field (double).
		 * @in msg Protobuf Message object
		 * @in field_name Name of field (as string).
		 * @in default_value Default value (default 0.0f)
		 * @in set_if_missing If true it will attempt to set the field if the value is uninitialised.
		 * @return Value of the field (or default_value if missing).
		 */
		inline double GetFloat(MESSAGE *msg, std::string field_name,
			double default_value = 0.0f, bool set_if_missing = false) {

			double out = 0.0f;

			const DESCRIPTOR *desc = msg->GetDescriptor();
			const REFLECTION *refl = msg->GetReflection();
			const FIELDDESC *field = desc->FindFieldByName(field_name);

			if (field != nullptr) {
				if (field->type() == FIELDDESC::TYPE_DOUBLE) {
					out = refl->GetDouble(*msg, field);
					if (out == 0.0f && set_if_missing) {
						refl->SetDouble(msg, field, default_value);
						out = default_value;
					}
				}
			}
			return out;
		}
#pragma endregion
#pragma region Int32
		/**
		 * @brief Sets the value of a field (int32_t)
		 * @in msg Protobuf Message object
		 * @in field_name Name of field (as string).
		 * @in value Value to be set.
		 * @return True if successful; false otherwise.
		 *
		 * Failure should typically only be because the field is missing.
		 */
		inline bool SetInt32(MESSAGE *msg,
			std::string field_name, int32_t value) {
			bool rv = false;
			const DESCRIPTOR *desc = msg->GetDescriptor();
			const REFLECTION *refl = msg->GetReflection();
			const FIELDDESC *field = desc->FindFieldByName(field_name);

			if (field != nullptr) {
				if (field->type() == FIELDDESC::TYPE_SFIXED32 ||
					field->type() == FIELDDESC::TYPE_SINT32) {
					refl->SetInt32(msg, field, value);
					rv = true;
				}
			}
			return rv;
		}

		/**
		 * @brief Gets the value of a field uint32_t).
		 * @in msg Protobuf Message object
		 * @in field_name Name of field (as string).
		 * @in default_value Default value (default false)
		 * @in set_if_missing If true it will attempt to set the field if the value is uninitialised.
		 * @return Value of the field (or default_value if missing).
		 */
		inline int32_t GetUInt32(MESSAGE *msg, std::string field_name,
			int32_t default_value = 0, bool set_if_missing = false) {

			int32_t out = 0;

			const DESCRIPTOR *desc = msg->GetDescriptor();
			const REFLECTION *refl = msg->GetReflection();
			const FIELDDESC *field = desc->FindFieldByName(field_name);

			if (field != nullptr) {
				if (field->type() == FIELDDESC::TYPE_SFIXED32 ||
					field->type() == FIELDDESC::TYPE_SINT32) {
					out = refl->GetInt32(*msg, field);
					if (out == 0 && set_if_missing) {
						refl->SetInt32(msg, field, default_value);
						out = default_value;
					}
				}
			}
			return out;
		}
#pragma endregion
#pragma region Int64
		/**
		 * @brief Sets the value of a field (int64_t)
		 * @in msg Protobuf Message object
		 * @in field_name Name of field (as string).
		 * @in value Value to be set.
		 * @return True if successful; false otherwise.
		 *
		 * Failure should typically only be because the field is missing.
		 */
		inline bool SetInt64(MESSAGE *msg,
			std::string field_name, int64_t value) {
			bool rv = false;
			const DESCRIPTOR *desc = msg->GetDescriptor();
			const REFLECTION *refl = msg->GetReflection();
			const FIELDDESC *field = desc->FindFieldByName(field_name);

			if (field != nullptr) {
				if (field->type() == FIELDDESC::TYPE_SFIXED64 ||
					field->type() == FIELDDESC::TYPE_SINT64) {
					refl->SetInt64(msg, field, value);
					rv = true;
				}
			}
			return rv;
		}

		/**
		 * @brief Gets the value of a field (int64_t).
		 * @in msg Protobuf Message object
		 * @in field_name Name of field (as string).
		 * @in default_value Default value (default 0)
		 * @in set_if_missing If true it will attempt to set the field if the value is uninitialised.
		 * @return Value of the field (or default_value if missing).
		 */
		inline int64_t GetInt64(MESSAGE *msg, std::string field_name,
			int64_t default_value = 0, bool set_if_missing = false) {

			int64_t out = 0;

			const DESCRIPTOR *desc = msg->GetDescriptor();
			const REFLECTION *refl = msg->GetReflection();
			const FIELDDESC *field = desc->FindFieldByName(field_name);

			if (field != nullptr) {
				if (field->type() == FIELDDESC::TYPE_SFIXED64 ||
					field->type() == FIELDDESC::TYPE_SINT64) {
					out = refl->GetInt64(*msg, field);
					if (out == 0 && set_if_missing) {
						refl->SetInt64(msg, field, default_value);
						out = default_value;
					}
				}
			}
			return out;
		}
#pragma endregion
#pragma region UInt32
		/**
		 * @brief Sets the value of a field (uint32_t)
		 * @in msg Protobuf Message object
		 * @in field_name Name of field (as string).
		 * @in value Value to be set.
		 * @return True if successful; false otherwise.
		 *
		 * Failure should typically only be because the field is missing.
		 */
		inline bool SetUInt32(MESSAGE *msg,
			std::string field_name, uint32_t value) {
			bool rv = false;
			const DESCRIPTOR *desc = msg->GetDescriptor();
			const REFLECTION *refl = msg->GetReflection();
			const FIELDDESC *field = desc->FindFieldByName(field_name);

			if (field != nullptr) {
				if (field->type() == FIELDDESC::TYPE_FIXED32 ||
					field->type() == FIELDDESC::TYPE_UINT32) {
					refl->SetUInt32(msg, field, value);
					rv = true;
				}
			}
			return rv;
		}

		/**
		 * @brief Gets the value of a field (uint32_t).
		 * @in msg Protobuf Message object
		 * @in field_name Name of field (as string).
		 * @in default_value Default value (default 0)
		 * @in set_if_missing If true it will attempt to set the field if the value is uninitialised.
		 * @return Value of the field (or default_value if missing).
		 */
		inline uint32_t GetUInt32(MESSAGE *msg, std::string field_name,
			uint32_t default_value = 0, bool set_if_missing = false) {

			uint32_t out = 0;

			const DESCRIPTOR *desc = msg->GetDescriptor();
			const REFLECTION *refl = msg->GetReflection();
			const FIELDDESC *field = desc->FindFieldByName(field_name);

			if (field != nullptr) {
				if (field->type() == FIELDDESC::TYPE_FIXED32 ||
					field->type() == FIELDDESC::TYPE_UINT32) {
					out = refl->GetUInt32(*msg, field);
					if (out == 0 && set_if_missing) {
						refl->SetUInt32(msg, field, default_value);
						out = default_value;
					}
				}
			}
			return out;
		}
#pragma endregion
#pragma region UInt64
		/**
		 * @brief Sets the value of a field (uint64_t)
		 * @in msg Protobuf Message object
		 * @in field_name Name of field (as string).
		 * @in value Value to be set.
		 * @return True if successful; false otherwise.
		 *
		 * Failure should typically only be because the field is missing.
		 */
		inline bool SetUInt64(MESSAGE *msg,
			std::string field_name, uint32_t value) {
			bool rv = false;
			const DESCRIPTOR *desc = msg->GetDescriptor();
			const REFLECTION *refl = msg->GetReflection();
			const FIELDDESC *field = desc->FindFieldByName(field_name);

			if (field != nullptr) {
				if (field->type() == FIELDDESC::TYPE_FIXED64 ||
					field->type() == FIELDDESC::TYPE_UINT64) {
					refl->SetUInt64(msg, field, value);
					rv = true;
				}
			}
			return rv;
		}

		/**
		 * @brief Gets the value of a field (uint64_t).
		 * @in msg Protobuf Message object
		 * @in field_name Name of field (as string).
		 * @in default_value Default value (default 0)
		 * @in set_if_missing If true it will attempt to set the field if the value is uninitialised.
		 * @return Value of the field (or default_value if missing).
		 */
		inline uint64_t GetUInt64(MESSAGE *msg, std::string field_name,
			uint64_t default_value = 0, bool set_if_missing=false) {

			uint64_t out = 0;

			const DESCRIPTOR *desc = msg->GetDescriptor();
			const REFLECTION *refl = msg->GetReflection();
			const FIELDDESC *field = desc->FindFieldByName(field_name);

			if (field != nullptr) {
				if (field->type() == FIELDDESC::TYPE_FIXED64 ||
					field->type() == FIELDDESC::TYPE_UINT64) {
					out = refl->GetUInt64(*msg, field);
					if (out == 0 && set_if_missing) {
						refl->SetUInt64(msg, field, default_value);
						out = default_value;
					}
				}
			}
			return out;
		}
#pragma endregion
#pragma region String
		/**
		 * @brief Sets the value of a field as a string.
		 * @in msg Protobuf Message object
		 * @in field_name Name of field (as string).
		 * @in value Value to be set.
		 * @return True if successful; false otherwise.
		 *
		 * Failure should typically only be because the field is missing.
		 */
		inline bool SetString(MESSAGE *msg, std::string field_name, std::string value) {
			bool rv = false;
			const DESCRIPTOR *desc = msg->GetDescriptor();
			const REFLECTION *refl = msg->GetReflection();
			const FIELDDESC *field = desc->FindFieldByName(field_name);

			if (field != nullptr) {
				if (field->type() == FIELDDESC::TYPE_STRING ||
					field->type() == FIELDDESC::TYPE_BYTES) {
					refl->SetString(msg, field, value);
					rv = true;
				}
			}
			return rv;
		}

		/**
		 * @brief Gets the value of a field as a string.
		 * @in msg Protobuf Message object
		 * @in field_name Name of field (as string).
		 * @in default_value Default value (default "")
		 * @in set_if_missing If true it will attempt to set the field if the value is uninitialised.
		 * @return Value of the field (or default_value if missing).
		 */
		inline std::string GetString(MESSAGE *msg, std::string field_name,
			std::string default_value = "", bool set_if_missing=false) {

			std::string out = "";

			const DESCRIPTOR *desc = msg->GetDescriptor();
			const REFLECTION *refl = msg->GetReflection();
			const FIELDDESC *field = desc->FindFieldByName(field_name);

			if (field->type() == FIELDDESC::TYPE_STRING ||
				field->type() == FIELDDESC::TYPE_BYTES) {
				out = refl->GetString(*msg, field);
				if (out == "" && set_if_missing) {
					refl->SetString(msg, field, default_value);
					out = default_value;
				}
			}
			return out;
		}
#pragma endregion
#pragma region Enum
		/**
		 * @brief Sets the value of an enum field by number
		 * @in msg Protobuf Message object
		 * @in field_name Name of field (as string).
		 * @in value Value to be set.
		 * @return True if successful; false otherwise.
		 *
		 * Failure should typically only be because the field is missing.
		 */
		inline bool SetEnum(MESSAGE *msg, std::string field_name, int32_t value) {
			bool rv = false;
			const DESCRIPTOR *desc = msg->GetDescriptor();
			const REFLECTION *refl = msg->GetReflection();
			const FIELDDESC *field = desc->FindFieldByName(field_name);

			if (field != nullptr) {
				if (field->type() == FIELDDESC::TYPE_ENUM) {

					const ::google::protobuf::EnumDescriptor *enum_desc =
						desc->FindEnumTypeByName(field->enum_type()->name());

					if (enum_desc != nullptr) {
						const ::google::protobuf::EnumValueDescriptor *enum_value_desc = nullptr;
						enum_value_desc = enum_desc->FindValueByNumber(value);
						if (enum_value_desc != nullptr) {
							refl->SetEnum(msg, field, enum_value_desc);
						}
					}
					rv = true;
				}
			}
			return rv;
		}

		/**
		 * @brief Gets the value of an enum field.
		 * @in msg Protobuf Message object
		 * @in field_name Name of field (as string).
		 * @in default_value Default value (default 0)
		 * @in set_if_missing If true it will attempt to set the field if the value is uninitialised.
		 * @return Value of the field (or default_value if missing).
		 */
		inline int32_t GetEnum(MESSAGE *msg, std::string field_name,
			int32_t default_value = 0, bool set_if_missing = false) {

			int32_t out = 0;

			const DESCRIPTOR *desc = msg->GetDescriptor();
			const REFLECTION *refl = msg->GetReflection();
			const FIELDDESC *field = desc->FindFieldByName(field_name);

			if (field != nullptr) {
				if (field->type() == FIELDDESC::TYPE_ENUM) {

					const ::google::protobuf::EnumDescriptor *enum_desc =
						desc->FindEnumTypeByName(field->enum_type()->name());

					std::string existing = refl->GetEnum(*msg, field)->name();
					auto current = enum_desc->FindValueByName(existing);
					out = current->number();

					if (out == -1 && set_if_missing) {
						refl->SetInt32(msg, field, default_value);
						out = default_value;
					}
				}
			}
			return out;
		}

		/** 
		 * @brief Gets the internal alias of a field (or the first for the value).
		 * @in msg Google Protocol Buffer message.
		 * @in field_name Name of the field to which this enum belongs.
		 * @in value (index)
		 * @return Alias as string (or "" for failure).
		 */
		inline std::string GetEnumAlias(MESSAGE *msg, ::std::string field_name,
			int32_t value = 0) {

			std::string out = "";

			const DESCRIPTOR *desc = msg->GetDescriptor();
			const REFLECTION *refl = msg->GetReflection();
			const FIELDDESC *field = desc->FindFieldByName(field_name);

			if (field != nullptr) {
				if (field->type() == FIELDDESC::TYPE_ENUM) {

					const ::google::protobuf::EnumDescriptor *enum_desc =
						desc->FindEnumTypeByName(field->enum_type()->name());
					auto inner_value = enum_desc->FindValueByNumber(value);
					out = inner_value->name();
				}
			}

			return out;
		}

#pragma endregion

		/**
		 * @brief Gets the value of a field as a string.
		 * @in msg Google Protocol Buffer Message.
		 * @in field_name Name of the field in question.
		 * @in indent Number of tabs before it (only applies to messages).
		 * @return Value of the field (or inline message) as string.
		 */
		inline std::string GetAsString(MESSAGE *msg, std::string field_name,
			int indent = 0) {

			std::string out = "";

			const DESCRIPTOR *desc = msg->GetDescriptor();
			const REFLECTION *refl = msg->GetReflection();
			const FIELDDESC *field = desc->FindFieldByName(field_name);
			if (field != nullptr) {
				FIELDDESC::Type ftype = field->type();
				std::stringstream ss;

				switch (ftype) {
				case FIELDDESC::TYPE_BYTES:
				case FIELDDESC::TYPE_STRING: {
					ss << refl->GetString(*msg, field);
				} break;

				case FIELDDESC::TYPE_BOOL: {
					ss << refl->GetBool(*msg, field);
				} break;

				case FIELDDESC::TYPE_DOUBLE: {
					ss << refl->GetDouble(*msg, field);
				} break;

				case FIELDDESC::TYPE_ENUM: {
					ss << refl->GetEnum(*msg, field)->full_name();
				} break;

				case FIELDDESC::TYPE_FIXED32:
				case FIELDDESC::TYPE_UINT32: {
					ss << refl->GetUInt32(*msg, field);
				} break;

				case FIELDDESC::TYPE_FIXED64:
				case FIELDDESC::TYPE_UINT64: {
					ss << refl->GetUInt64(*msg, field);
				} break;

				case FIELDDESC::TYPE_FLOAT: {
					ss << refl->GetFloat(*msg, field);
				} break;

				case FIELDDESC::TYPE_GROUP: {
					// unhandled
				} break;

				case FIELDDESC::TYPE_MESSAGE:{
					// Should be done with an immutable type
					// but this saves a bunch of casting.
					ss << Dump(refl->MutableMessage(msg, field), indent+1);
				} break;

				case FIELDDESC::TYPE_SFIXED32:
				case FIELDDESC::TYPE_INT32: {
					ss << refl->GetInt32(*msg, field);
				} break;

				case FIELDDESC::TYPE_SFIXED64:
				case FIELDDESC::TYPE_INT64: {
					ss << refl->GetInt64(*msg, field);
				} break;

				default: {
					ss << "[unimplemented type handler]";
				} break;


				}
				out = ss.str();
			}
			return out;
		}

		/**
		 * @brief Processes the vectored argc/argv into a message (where fields match).
		 * @in vec vector of argc/argv.
		 * @in msg A Google Protocol Buffers message.
		 * @in force_lowercase If true the field will be searched for in lowercase.
		 *
		 * This variant allows for iteration.
		 */
		inline void Parse(std::vector<std::string> &vec,
			MESSAGE* msg, bool force_lowercase = false) {

			// If it is NOT a Protocol Buffer message we are wasting our time
			// and heading towards a segfault.
			if (msg == nullptr) {
				return;
			}

			// Get the descriptor
			// - This is the 'descriptor'/description of the message.
			const DESCRIPTOR *descriptor = msg->GetDescriptor();

			// Get the refl
			// - This allows for loking into fields for information.
			const REFLECTION *refl = msg->GetReflection();

			// Field descriptor (used below)
			const FIELDDESC *field_descriptor = nullptr;

			// Holder for argv for C++ string manipulation.
			std::string arg;

			// The following two variables are: '--<key>=<val>'
			std::string key;
			std::string val;

			// Position (usually of '=')
			size_t pos;

			// Iterate through the incoming arguments
			for (auto arg : vec) {
				pos = arg.find("=");
				if (pos > 0) {
					key = arg.substr(0, pos);
					val = arg.substr(pos + 1, arg.length());
					field_descriptor = nullptr;
					if (force_lowercase) {
						std::transform(key.begin(), key.end(), key.begin(), ::tolower);
						field_descriptor = descriptor->FindFieldByLowercaseName(key);
					}
					else {
						field_descriptor = descriptor->FindFieldByName(key);
					}

					// If the field descriptor exists
					if (field_descriptor != nullptr) {

						switch (field_descriptor->type()) {
						case FIELDDESC::TYPE_BOOL: {
							std::transform(val.begin(), val.end(), val.begin(), ::tolower);
							if (val == "true" || val == "1") {
								refl->SetBool(msg, field_descriptor, true);
							}
							else {
								refl->SetBool(msg, field_descriptor, false);
							}
						} break;

						case FIELDDESC::TYPE_BYTES:
						case FIELDDESC::TYPE_STRING: {
							refl->SetString(msg, field_descriptor, val);
						} break;

						case FIELDDESC::TYPE_DOUBLE: {
							refl->SetDouble(msg, field_descriptor, std::stod(val));
						} break;

						case FIELDDESC::TYPE_ENUM: {

							// Attempt to get the enum descriptor
							const ::google::protobuf::EnumDescriptor *enum_desc =
								descriptor->FindEnumTypeByName(field_descriptor->enum_type()->name());

							if (enum_desc != nullptr) {
								const ::google::protobuf::EnumValueDescriptor *enum_value_desc = nullptr;

								// try incoming
								enum_value_desc = enum_desc->FindValueByName(val);
								if (enum_value_desc == nullptr) {
									// try lower
									std::transform(val.begin(), val.end(), val.begin(), ::tolower);
									enum_value_desc = enum_desc->FindValueByName(val);
									if (enum_value_desc == nullptr) {
										// try upper 
										std::transform(val.begin(), val.end(), val.begin(), ::toupper);
										enum_value_desc = enum_desc->FindValueByName(val);
										if (enum_value_desc == nullptr) {
											// try number
											int ival = std::stol(val);
											enum_value_desc = enum_desc->FindValueByNumber(ival);
										}
									}
								}

								// If we have a value, update enum_value
								if (enum_value_desc != nullptr) {
									refl->SetEnum(msg, field_descriptor, enum_value_desc);
								}
							}
						} break;

						case FIELDDESC::TYPE_FIXED32:
						case FIELDDESC::TYPE_UINT32: {
							refl->SetUInt32(msg, field_descriptor, std::stoul(val));
						} break;

						case FIELDDESC::TYPE_FIXED64:
						case FIELDDESC::TYPE_UINT64: {
							refl->SetUInt64(msg, field_descriptor, std::stoull(val));
						} break;

						case FIELDDESC::TYPE_FLOAT: {
							refl->SetFloat(msg, field_descriptor, std::stof(val));
						} break;

						case FIELDDESC::TYPE_GROUP: {
							// todo ?
							// - Probably shouldn't be used anyway.
						} break;

						case FIELDDESC::TYPE_MESSAGE:{
							// Experimental and unrecommended.

							// Get the value as a string stream
							std::stringstream ss(val);

							// Set iteration pointers
							std::istream_iterator<std::string> begin(ss);
							std::istream_iterator<std::string> end;

							// Set storage
							std::vector<std::string> internal_vec(begin, end);

							// -- STL MAGIC -- Tokens!

							// Get the internal message from the field descriptor.
							MESSAGE *internal_message = refl->MutableMessage(msg, field_descriptor);

							// Now process it ...
							Parse(internal_vec, internal_message, force_lowercase);
						} break;

						case FIELDDESC::TYPE_SFIXED32:
						case FIELDDESC::TYPE_INT32: {
							refl->SetInt32(msg, field_descriptor, std::stol(val));
						} break;

						case FIELDDESC::TYPE_SFIXED64:
						case FIELDDESC::TYPE_INT64: {
							refl->SetInt64(msg, field_descriptor, std::stoll(val));
						} break;

							// Problem or out of date support.
						default: break;
						}
					}
				}
			}
		}

		/**
		 * @brief Processes argc/argv into a message (where fields match).
		 * @in argc 'argc' from the main function/entry point.
		 * @in argv 'argv' from the main function/entry point.
		 * @in msg A Google Protocol Buffer message.
		 * @in force_lowercase If true the field will be searched for in lowercase.
		 */
		inline void Parse(int argc, char **argv,
			MESSAGE *msg, bool force_lowercase = false) {

			// If it is NOT a Protocol Buffer message we are wasting our time
			// and heading towards a segfault.
			if (msg == nullptr) {
				return;
			}

			// Turn it into a vector
			std::vector<std::string> args;
			std::string arg;
			for (int i = 1; i < argc; i++) {
				if (argv[i][0] == '-' && argv[i][1] == '-') {
					arg = std::string(argv[i]);
					arg = arg.substr(2, arg.length());
					args.push_back(std::string(arg));
				}
			}

			// Call the actual parser now.
			Parse(args, msg, force_lowercase);
		}

		/**
		 * @brief Dumps a Message to string.
		 */
		inline std::string Dump(MESSAGE *msg, int indent = 0) {
			const DESCRIPTOR *desc = msg->GetDescriptor();
			const REFLECTION *refl = msg->GetReflection();
			const FIELDDESC *field;

			std::stringstream ss;
			std::string fname;
			std::string out;
			int count = desc->field_count();
			for (int i = 0; i < count; i++) {
				field = desc->field(i);
				fname = field->name();

				for (int j = 0; j < indent; j++) {
					ss << "\t";
				}

				if (field->type() == FIELDDESC::TYPE_MESSAGE) {
					ss << "[message] `" << fname << "'" << std::endl;
					ss << GetAsString(msg, fname, indent);
				} else {
					ss << "`" << fname << "' = `"
						<< GetAsString(msg, fname, indent)
						<< "'\n";
				}
			}
			out = ss.str();
			return out;
		}
	}
}

// Remove helpers
#undef MESSAGE
#undef DESCRIPTOR
#undef REFLECTION
#undef FIELDDESC

#endif // _AWS_PROTOPARSER_HPP_
