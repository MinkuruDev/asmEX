#pragma once
#include <string>
#include <cstdint>
#include <sstream>
#include <iomanip>
struct YmmVal
{
public:
	union
	{
		int8_t m_I8[32];
		int16_t m_I16[16];
		int32_t m_I32[8];
		int64_t m_I64[4];
		uint8_t m_U8[32];
		uint16_t m_U16[16];
		uint32_t m_U32[8];
		uint64_t m_U64[4];
		float m_F32[8];
		double m_F64[4];
	};

	float ToStringF32(int i) {
		return m_F32[i];
	}

	double ToStringF64(int i) {
		return m_F64[i];
	}
};
