#pragma once
#include <string>
#include <cstdint>
#include <sstream>
#include <iomanip>
struct ZmmVal
{
public:
	union
	{
		int8_t m_I8[64];
		int16_t m_I16[32];
		int32_t m_I32[16];
		int64_t m_I64[8];
		uint8_t m_U8[64];
		uint16_t m_U16[32];
		uint32_t m_U32[16];
		uint64_t m_U64[8];
		float m_F32[16];
		double m_F64[8];
	};

	float ToStringF32(int i) {
		return m_F32[i];
	}

	double ToStringF64(int i) {
		return m_F64[i];
	}
};