#ifndef AGS_LIB_ALLEGRO_SURFACE_SIMD_NEON_H
#define AGS_LIB_ALLEGRO_SURFACE_SIMD_NEON_H

#include "ags/lib/allegro/surface.h"

namespace AGS3 {

inline uint32x4_t simd2BppTo4Bpp(uint16x4_t pixels) {
	uint32x4_t x = vmovl_u16(pixels);
	uint32x4_t c = vshrq_n_u32(x, 11);
	uint32x4_t r = vshlq_n_u32(vorrq_u32(vshlq_n_u32(c, 3), vshrq_n_u32(c, 2)), 16);
	c = vshrq_n_u32(vandq_u32(x, vmovq_n_u32(0x07e0)), 5);
	uint32x4_t g = vshlq_n_u32(vorrq_u32(vshlq_n_u32(c, 2), vshrq_n_u32(c, 4)), 8);
	c = vandq_u32(x, vmovq_n_u32(0x001f));
	uint32x4_t b = vorrq_u32(vshlq_n_u32(c, 3), vshrq_n_u32(c, 2));
	return vorrq_u32(vorrq_u32(vorrq_u32(r, g), b), vmovq_n_u32(0xff000000));
}

inline uint16x4_t simd4BppTo2Bpp(uint32x4_t pixels) {
	uint32x4_t x = vshrq_n_u32(vandq_u32(pixels, vmovq_n_u32(0x000000ff)), 3);
	x = vorrq_u32(x, vshlq_n_u32(vshrq_n_u32(vandq_u32(pixels, vmovq_n_u32(0x0000ff00)), 8+2), 5));
	x = vorrq_u32(x, vshlq_n_u32(vshrq_n_u32(vandq_u32(pixels, vmovq_n_u32(0x00ff0000)), 16+3), 11));
	return vmovn_u32(x);
}

inline uint16x8_t rgbBlendSIMD2Bpp(uint16x8_t srcCols, uint16x8_t destCols, uint16x8_t alphas) {
	alphas = vaddq_u16(alphas, vandq_u16(vceqq_u16(alphas, vmovq_n_u16(0)), vmovq_n_u16(1)));
	uint16x8_t srcComps[] = {
		vandq_u16(srcCols, vmovq_n_u16(0x1f)),
		vandq_u16(vshrq_n_u16(srcCols, 5), vmovq_n_u16(0x3f)),
		vshrq_n_u16(srcCols, 11),
	}, destComps[] = {
		vandq_u16(destCols, vmovq_n_u16(0x1f)),
		vandq_u16(vshrq_n_u16(destCols, 5), vmovq_n_u16(0x3f)),
		vshrq_n_u16(destCols, 11),
	};
	//srcComps[0] = vorrq_u16(vshlq_n_u16(srcComps[0], 3), vshrq_n_u16(srcComps[0], 2));
	//srcComps[1] = vorrq_u16(vshlq_n_u16(srcComps[1], 2), vshrq_n_u16(srcComps[1], 4));
	//srcComps[2] = vorrq_u16(vshlq_n_u16(srcComps[2], 3), vshrq_n_u16(srcComps[2], 2));
	//destComps[0] = vorrq_u16(vshlq_n_u16(destComps[0], 3), vshrq_n_u16(destComps[0], 2));
	//destComps[1] = vorrq_u16(vshlq_n_u16(destComps[1], 2), vshrq_n_u16(destComps[1], 4));
	//destComps[2] = vorrq_u16(vshlq_n_u16(destComps[2], 3), vshrq_n_u16(destComps[2], 2));

	uint16x8_t diffs[] = {
		vsubq_u16(srcComps[0], destComps[0]), // B
		vsubq_u16(srcComps[1], destComps[1]), // G
		vsubq_u16(srcComps[2], destComps[2]), // R
	};
	alphas = vshrq_n_u16(alphas, 2);
	diffs[1] = vshrq_n_u16(vmulq_u16(diffs[1], alphas), 6);
	alphas = vshrq_n_u16(alphas, 1);
	diffs[0] = vshrq_n_u16(vmulq_u16(diffs[0], alphas), 5);
	diffs[2] = vshrq_n_u16(vmulq_u16(diffs[2], alphas), 5);

	//diffs[0] = vandq_u16(vshrq_n_u16(vaddq_u16(diffs[0], destComps[0]), 3), vmovq_n_u16(0x1f));
	//diffs[1] = vandq_u16(vshrq_n_u16(vaddq_u16(diffs[1], destComps[1]), 2), vmovq_n_u16(0x3f));
	//diffs[2] = vandq_u16(vshrq_n_u16(vaddq_u16(diffs[2], destComps[2]), 3), vmovq_n_u16(0x1f));

	diffs[0] = vandq_u16(vaddq_u16(diffs[0], destComps[0]), vmovq_n_u16(0x1f));
	diffs[1] = vandq_u16(vaddq_u16(diffs[1], destComps[1]), vmovq_n_u16(0x3f));
	diffs[2] = vandq_u16(vaddq_u16(diffs[2], destComps[2]), vmovq_n_u16(0x1f));
	diffs[0] = vorrq_u16(diffs[0], vshlq_n_u16(diffs[1], 5));
	return vorrq_u16(diffs[0], vshlq_n_u16(diffs[2], 11));
}

inline uint32x4_t rgbBlendSIMD(uint32x4_t srcCols, uint32x4_t destCols, uint32x4_t alphas, bool preserveAlpha) {
	alphas = vaddq_u32(alphas, vandq_u32(vcgtq_u32(alphas, vmovq_n_u32(0)), vmovq_n_u32(1)));
	uint32x4_t alpha = vandq_u32(destCols, vmovq_n_u32(0xff000000));
	uint32x4_t srcColsCopy = srcCols;
	srcColsCopy = vandq_u32(srcColsCopy, vmovq_n_u32(0xff00ff));
	uint32x4_t destColsCopy = destCols;
	destColsCopy = vandq_u32(destColsCopy, vmovq_n_u32(0xff00ff));
	srcColsCopy = vsubq_u32(srcColsCopy, destColsCopy);
	srcColsCopy = vmulq_u32(srcColsCopy, alphas);
	srcColsCopy = vshrq_n_u32(srcColsCopy, 8);
	srcColsCopy = vaddq_u32(srcColsCopy, destCols);

	srcCols = vandq_u32(srcCols, vmovq_n_u32(0xff00));
	destCols = vandq_u32(destCols, vmovq_n_u32(0xff00));
	srcCols = vsubq_u32(srcCols, destCols);
	srcCols = vmulq_u32(srcCols, alphas);
	srcCols = vshrq_n_u32(srcCols, 8);
	srcCols = vaddq_u32(srcCols, destCols);
	srcColsCopy = vandq_u32(srcColsCopy, vmovq_n_u32(0xff00ff));
	srcCols = vandq_u32(srcCols, vmovq_n_u32(0xff00));
	srcCols = vorrq_u32(srcCols, srcColsCopy);
	if (preserveAlpha) {
		srcCols = vandq_u32(srcCols, vmovq_n_u32(0x00ffffff));
		srcCols = vorrq_u32(srcCols, alpha);
	}
	return srcCols;
}

inline uint32x4_t argbBlendSIMD(uint32x4_t srcCols, uint32x4_t destCols) {
	float16x4_t sAlphas = vcvt_f16_f32(vcvtq_f32_u32(vshrq_n_u32(srcCols, 24)));
	sAlphas = vmul_n_f16(sAlphas, 1.0 / 255.0);
	float16x8_t sAlphas1 = vcombine_f16(vmov_n_f16(vduph_lane_f16(sAlphas, 0)), vmov_n_f16(vduph_lane_f16(sAlphas, 1)));
	float16x8_t sAlphas2 = vcombine_f16(vmov_n_f16(vduph_lane_f16(sAlphas, 2)), vmov_n_f16(vduph_lane_f16(sAlphas, 3)));
	float16x4_t dAlphas = vcvt_f16_f32(vcvtq_f32_u32(vshrq_n_u32(destCols, 24)));
	dAlphas = vmul_n_f16(dAlphas, 1.0 / 255.0);
	dAlphas = vmul_f16(dAlphas, vsub_f16(vmov_n_f16(1.0), sAlphas));
	float16x8_t dAlphas1 = vcombine_f16(vmov_n_f16(vduph_lane_f16(dAlphas, 0)), vmov_n_f16(vduph_lane_f16(dAlphas, 1)));
	float16x8_t dAlphas2 = vcombine_f16(vmov_n_f16(vduph_lane_f16(dAlphas, 2)), vmov_n_f16(vduph_lane_f16(dAlphas, 3)));
	float16x8_t srcRgb1 = vcvtq_f16_u16(vmovl_u8(vreinterpret_u8_u32(vget_low_u32(srcCols))));
	float16x8_t destRgb1 = vcvtq_f16_u16(vmovl_u8(vreinterpret_u8_u32(vget_low_u32(destCols))));
	float16x8_t srcRgb2 = vcvtq_f16_u16(vmovl_u8(vreinterpret_u8_u32(vget_high_u32(srcCols))));
	float16x8_t destRgb2 = vcvtq_f16_u16(vmovl_u8(vreinterpret_u8_u32(vget_high_u32(destCols))));
	srcRgb1 = vmulq_f16(srcRgb1, sAlphas1);
	destRgb1 = vmulq_f16(destRgb1, dAlphas1);
	srcRgb1 = vaddq_f16(srcRgb1, destRgb1);
	float16x8_t alphasRec = vrecpeq_f16(vaddq_f16(sAlphas1, dAlphas1));
	srcRgb1 = vmulq_f16(srcRgb1, alphasRec);
	srcRgb2 = vmulq_f16(srcRgb2, sAlphas2);
	destRgb2 = vmulq_f16(destRgb2, dAlphas2);
	srcRgb2 = vaddq_f16(srcRgb2, destRgb2);
	alphasRec = vrecpeq_f16(vaddq_f16(sAlphas2, dAlphas2));
	srcRgb2 = vmulq_f16(srcRgb2, alphasRec);
	uint16x4_t alphas = vcvta_u16_f16(vmul_n_f16(vadd_f16(sAlphas, dAlphas), 255.0));
	uint16x8_t uintSrcRgb1 = vcvtq_u16_f16(srcRgb1), uintSrcRgb2 = vcvtq_u16_f16(srcRgb2);
	uintSrcRgb1 = vcopyq_lane_u16(uintSrcRgb1, 3, alphas, 0);
	uintSrcRgb1 = vcopyq_lane_u16(uintSrcRgb1, 7, alphas, 1);
	uintSrcRgb2 = vcopyq_lane_u16(uintSrcRgb2, 3, alphas, 2);
	uintSrcRgb2 = vcopyq_lane_u16(uintSrcRgb2, 7, alphas, 3);
	return vcombine_u32(vreinterpret_u32_u8(vmovn_u16(uintSrcRgb1)), vreinterpret_u32_u8(vmovn_u16(uintSrcRgb2)));
}

inline uint32x4_t blendTintSpriteSIMD(uint32x4_t srcCols, uint32x4_t destCols, uint32x4_t alphas, bool light) {
	// This function is NOT 1 to 1 with the original... It just approximates it
	// It gets the value of the dest color
	// Then it gets the h and s of the srcCols

	// srcCols[0] = A | R | G | B
	// srcCols[1] = A | R | G | B
	// srcCols[2] = A | R | G | B
	// srcCols[3] = A | R | G | B
	//  ->
	// dda = { A[0], A[1], A[2], A[3] }
	// ddr = { R[0], R[1], R[2], R[3] }
	// ddg = { G[0], G[1], G[2], G[3] }
	// ddb = { B[0], B[1], B[2], B[3] }

	float32x4_t ddr, ddg, ddb;
	ddr = vmulq_n_f32(vcvtq_f32_u32(vandq_u32(vshrq_n_u32(destCols, 16), vmovq_n_u32(0xff))), 1.0 / 255.0);
	ddg = vmulq_n_f32(vcvtq_f32_u32(vandq_u32(vshrq_n_u32(destCols, 8), vmovq_n_u32(0xff))), 1.0 / 255.0);
	ddb = vmulq_n_f32(vcvtq_f32_u32(vandq_u32(destCols, vmovq_n_u32(0xff))), 1.0 / 255.0);
	float32x4_t ssr, ssg, ssb;
	ssr = vmulq_n_f32(vcvtq_f32_u32(vandq_u32(vshrq_n_u32(srcCols, 16), vmovq_n_u32(0xff))), 1.0 / 255.0);
	ssg = vmulq_n_f32(vcvtq_f32_u32(vandq_u32(vshrq_n_u32(srcCols, 8), vmovq_n_u32(0xff))), 1.0 / 255.0);
	ssb = vmulq_n_f32(vcvtq_f32_u32(vandq_u32(srcCols, vmovq_n_u32(0xff))), 1.0 / 255.0);
	float32x4_t dmaxes = vmaxq_f32(ddr, vmaxq_f32(ddg, ddb));
	float32x4_t smaxes = vmaxq_f32(ssr, vmaxq_f32(ssg, ssb));
	//float32x4_t dmins = vminq_f32(ddr, vminq_f32(ddg, ddb));
	float32x4_t smins = vminq_f32(ssr, vminq_f32(ssg, ssb));
	//float32x4_t ddelta = vsubq_f32(dmaxes, dmins);
	
	const float32x4_t eplison0 = vmovq_n_f32(0.0000001);
	float32x4_t chroma = vmaxq_f32(vsubq_f32(smaxes, smins), eplison0);
	float32x4_t hr, hg, hb, hue;
	hr = vdivq_f32(vsubq_f32(ssg, ssb), chroma);
	hr = vsubq_f32(hr, vmulq_n_f32(vrndmq_f32(vmulq_n_f32(hr, 1.0 / 6.0)), 6.0));
	hg = vaddq_f32(vdivq_f32(vsubq_f32(ssb, ssr), chroma), vmovq_n_f32(2.0));
	hb = vaddq_f32(vdivq_f32(vsubq_f32(ssr, ssg), chroma), vmovq_n_f32(4.0));
	float32x4_t hrfactors = vcvtq_f32_u32(vandq_u32(vandq_u32(vceqq_f32(ssr, smaxes), vmvnq_u32(vceqq_u32(ssr, ssb))), vmovq_n_u32(1)));
	float32x4_t hgfactors = vcvtq_f32_u32(vandq_u32(vandq_u32(vceqq_f32(ssg, smaxes), vmvnq_u32(vceqq_u32(ssg, ssr))), vmovq_n_u32(1)));
	float32x4_t hbfactors = vcvtq_f32_u32(vandq_u32(vandq_u32(vceqq_f32(ssb, smaxes), vmvnq_u32(vceqq_u32(ssb, ssg))), vmovq_n_u32(1)));
	hue = vmulq_f32(hr, hrfactors);
	hue = vaddq_f32(hue, vmulq_f32(hg, hgfactors));
	hue = vaddq_f32(hue, vmulq_f32(hb, hbfactors));
	//float32x4_t hchromaZeroMask = vcvtq_f32_u32(vandq_u32(vcleq_f32(chroma, eplison0), vmovq_n_u32(1)));
	//hue = vmulq_f32(hue, hchromaZeroMask);

	// Mess with the light
	float32x4_t val = dmaxes;
	if (light) {
		val = vsubq_f32(val, vsubq_f32(vmovq_n_f32(1.0), vmulq_n_f32(vcvtq_f32_u32(alphas), 1.0 / 250.0)));
		val = vmaxq_f32(val, vmovq_n_f32(0.0));
	}
		
	// then it stiches them back together
	//AGS3::Shared::Debug::Printf(AGS3::Shared::kDbgMsg_Info, "hues: %f", vgetq_lane_f32(hue, 0));
	chroma = vmulq_f32(val, vdivq_f32(vsubq_f32(smaxes, smins), vaddq_f32(smaxes, eplison0)));
	float32x4_t hprime_mod2 = vmulq_n_f32(hue, 1.0 / 2.0);
	hprime_mod2 = vmulq_n_f32(vsubq_f32(hprime_mod2, vrndmq_f32(hprime_mod2)), 2.0);
	float32x4_t x = vmulq_f32(chroma, vsubq_f32(vmovq_n_f32(1.0), vabsq_f32(vsubq_f32(hprime_mod2, vmovq_n_f32(1.0)))));
	uint32x4_t hprime_rounded = vcvtq_u32_f32(hue);
	uint32x4_t x_int = vcvtq_u32_f32(vmulq_n_f32(x, 255.0));
	uint32x4_t c_int = vcvtq_u32_f32(vmulq_n_f32(chroma, 255.0));

	uint32x4_t val0 = vorrq_u32(vshlq_n_u32(x_int, 8), vshlq_n_u32(c_int, 16));
	val0 = vandq_u32(val0, vorrq_u32(vceqq_u32(hprime_rounded, vmovq_n_u32(0)), vceqq_u32(hprime_rounded, vmovq_n_u32(6))));
	uint32x4_t val1 = vorrq_u32(vshlq_n_u32(c_int, 8), vshlq_n_u32(x_int, 16));
	val1 = vandq_u32(val1, vceqq_u32(hprime_rounded, vmovq_n_u32(1)));
	uint32x4_t val2 = vorrq_u32(vshlq_n_u32(c_int, 8), x_int);
	val2 = vandq_u32(val2, vceqq_u32(hprime_rounded, vmovq_n_u32(2)));
	uint32x4_t val3 = vorrq_u32(vshlq_n_u32(x_int, 8), c_int);
	val3 = vandq_u32(val3, vceqq_u32(hprime_rounded, vmovq_n_u32(3)));
	uint32x4_t val4 = vorrq_u32(vshlq_n_u32(x_int, 16), c_int);
	val4 = vandq_u32(val4, vceqq_u32(hprime_rounded, vmovq_n_u32(4)));
	uint32x4_t val5 = vorrq_u32(vshlq_n_u32(c_int, 16), x_int);
	val5 = vandq_u32(val5, vceqq_u32(hprime_rounded, vmovq_n_u32(5)));

	uint32x4_t final = vorrq_u32(val0, vorrq_u32(val1, vorrq_u32(val2, vorrq_u32(val3, vorrq_u32(val4, val5)))));
	uint32x4_t val_add = vcvtq_u32_f32(vmulq_n_f32(vsubq_f32(val, chroma), 255.0));
	val_add = vorrq_u32(val_add, vorrq_u32(vshlq_n_u32(val_add, 8), vorrq_u32(vshlq_n_u32(val_add, 16), vandq_u32(destCols, vmovq_n_u32(0xff000000)))));
	final = vaddq_u32(final, val_add);
	return final;
}

inline uint32x4_t blendPixelSIMD(uint32x4_t srcCols, uint32x4_t destCols, uint32x4_t alphas) {
	uint32x4_t srcAlphas, difAlphas, mask, ch1, ch2;
	auto setupArgbAlphas = [&]() {
		srcAlphas = vshrq_n_u32(srcCols, 24);
		difAlphas = vaddq_u32(vandq_u32(alphas, vmovq_n_u32(0xff)), vmovq_n_u32(1));
		difAlphas = vshrq_n_u32(vmulq_u32(srcAlphas, difAlphas), 8);
		difAlphas = vshlq_n_u32(difAlphas, 24);
		srcAlphas = vshlq_n_u32(srcAlphas, 24);
		mask = vceqq_u32(alphas, vmovq_n_u32(0));
		srcAlphas = vandq_u32(srcAlphas, mask);
		difAlphas = vandq_u32(difAlphas, vmvnq_u32(mask));
		srcCols = vandq_u32(srcCols, vmovq_n_u32(0x00ffffff));
		srcCols = vorrq_u32(srcCols, vorrq_u32(srcAlphas, difAlphas));
	};
	switch (_G(_blender_mode)) {
	case kSourceAlphaBlender:
		alphas = vshrq_n_u32(srcCols, 24);
		return rgbBlendSIMD(srcCols, destCols, alphas, false);
	case kArgbToArgbBlender:
		setupArgbAlphas();
		mask = vcgtq_u32(vshrq_n_u32(srcCols, 24), vmovq_n_u32(0));
		ch1 = vandq_u32(argbBlendSIMD(srcCols, destCols), mask);
		ch2 = vandq_u32(destCols, vmvnq_u32(mask));
		return vorrq_u32(ch1, ch2);
	case kArgbToRgbBlender:
		setupArgbAlphas();
		return rgbBlendSIMD(srcCols, destCols, vshrq_n_u32(srcCols, 24), false);
		//mask = vcgtq_u32(vshrq_n_u32(srcCols, 24), vmovq_n_u32(0));
		//ch1 = vandq_u32(argbBlendSIMD(srcCols, destCols), mask);
		//ch2 = vandq_u32(destCols, vmvnq_u32(mask));
		//return vandq_u32(vorrq_u32(ch1, ch2), vmovq_n_u32(0x00ffffff));
	case kRgbToArgbBlender:
		ch2 = vandq_u32(srcCols, vmovq_n_u32(0x00ffffff));
		ch2 = vorrq_u32(ch2, vshlq_n_u32(alphas, 24));
		ch2 = argbBlendSIMD(ch2, destCols);
		ch1 = vorrq_u32(srcCols, vmovq_n_u32(0xff000000));
		mask = vorrq_u32(vceqq_u32(alphas, vmovq_n_u32(0)), vceqq_u32(alphas, vmovq_n_u32(0xff)));
		ch1 = vandq_u32(ch1, mask);
		ch2 = vandq_u32(ch2, vmvnq_u32(mask));
		return vorrq_u32(ch1, ch2);
	case kRgbToRgbBlender:
		return rgbBlendSIMD(srcCols, destCols, alphas, false);
	case kAlphaPreservedBlenderMode:
		return rgbBlendSIMD(srcCols, destCols, alphas, true);
	case kOpaqueBlenderMode:
		return vorrq_u32(srcCols, vmovq_n_u32(0xff000000));
	case kAdditiveBlenderMode:
		srcAlphas = vaddq_u32(vshrq_n_u32(srcCols, 24), vshrq_n_u32(destCols, 24));
		srcAlphas = vminq_u32(srcAlphas, vmovq_n_u32(0xff));
		srcCols = vandq_u32(srcCols, vmovq_n_u32(0x00ffffff));
		return vorrq_u32(srcCols, vshlq_n_u32(srcAlphas, 24));
	case kTintBlenderMode:
		return blendTintSpriteSIMD(srcCols, destCols, alphas, false);
	case kTintLightBlenderMode:
		return blendTintSpriteSIMD(srcCols, destCols, alphas, true);
	}
}

inline uint16x8_t blendPixelSIMD2Bpp(uint16x8_t srcCols, uint16x8_t destCols, uint16x8_t alphas) {
	uint16x8_t mask, ch1, ch2;
	switch (_G(_blender_mode)) {
	case kSourceAlphaBlender:
	case kOpaqueBlenderMode:
	case kAdditiveBlenderMode:
		return srcCols;
	case kArgbToArgbBlender:
	case kArgbToRgbBlender:
		ch1 = vandq_u16(vmovq_n_u16(0xff), vceqq_u16(alphas, vmovq_n_u16(0)));
		ch2 = vandq_u16(alphas, vcgtq_u16(alphas, vmovq_n_u16(0)));
		alphas = vorrq_u16(ch1, ch2);
	case kRgbToRgbBlender:
	case kAlphaPreservedBlenderMode:
		return rgbBlendSIMD2Bpp(srcCols, destCols, alphas);
	case kRgbToArgbBlender:
		mask = vorrq_u32(vceqq_u32(alphas, vmovq_n_u32(0)), vceqq_u32(alphas, vmovq_n_u32(255)));
		ch1 = vandq_u32(srcCols, mask);
		ch2 = vandq_u32(rgbBlendSIMD2Bpp(srcCols, destCols, alphas), vmvnq_u32(mask));
		return vorrq_u32(ch1, ch2);
	case kTintBlenderMode:
	case kTintLightBlenderMode:
		uint32x4_t srcColsLo = simd2BppTo4Bpp(vget_low_u16(srcCols));
		uint32x4_t srcColsHi = simd2BppTo4Bpp(vget_high_u16(srcCols));
		uint32x4_t destColsLo = simd2BppTo4Bpp(vget_low_u16(destCols));
		uint32x4_t destColsHi = simd2BppTo4Bpp(vget_high_u16(destCols));
		uint32x4_t alphasLo = vmovl_u16(vget_low_u16(alphas));
		uint32x4_t alphasHi = vmovl_u16(vget_high_u16(alphas));
		uint16x4_t lo = simd4BppTo2Bpp(blendTintSpriteSIMD(srcColsLo, destColsLo, alphasLo, _G(_blender_mode) == kTintLightBlenderMode));
		uint16x4_t hi = simd4BppTo2Bpp(blendTintSpriteSIMD(srcColsHi, destColsHi, alphasHi, _G(_blender_mode) == kTintLightBlenderMode));
		return vcombine_u16(lo, hi);
	}
}

template<int DestBytesPerPixel, int SrcBytesPerPixel>
inline void drawPixelSIMD(byte *destPtr, const byte *srcP2, uint32x4_t tint, uint32x4_t alphas, uint32x4_t maskedAlphas, uint32x4_t transColors, int xDir, int xCtrBpp, int srcAlpha, int skipTrans, bool horizFlip, bool useTint, uint32x4_t skipMask) {
	uint32x4_t srcCols, destCol;
	if (SrcBytesPerPixel == 4) {
		destCol = vld1q_u32((uint32 *)destPtr);
		srcCols = vld1q_u32((const uint32 *)(srcP2 + xDir * xCtrBpp));
	} else {
		destCol = simd2BppTo4Bpp(vld1_u16((uint16 *)destPtr));
		srcCols = simd2BppTo4Bpp(vld1_u16((const uint16 *)(srcP2 + xDir * xCtrBpp)));
	}
	uint32x4_t anded = vandq_u32(srcCols, maskedAlphas);
	if (srcAlpha != -1) {
		// take into account for useTint
		if (useTint) {
			srcCols = blendPixelSIMD(tint, srcCols, alphas);
		} else {
			srcCols = blendPixelSIMD(srcCols, destCol, alphas);
		}
	}
	uint32x4_t mask1 = skipTrans ? vceqq_u32(anded, transColors) : vmovq_n_u32(0);
	mask1 = vorrq_u32(mask1, skipMask);
	uint32x4_t destCols2 = vandq_u32(destCol, mask1);
	uint32x4_t srcCols2 = vandq_u32(srcCols, vmvnq_u32(mask1));
	uint32x4_t final = vorrq_u32(destCols2, srcCols2);
	if (horizFlip) {
		final = vrev64q_u32(final);
		final = vcombine_u32(vget_high_u32(final), vget_low_u32(final));
	}
	if (DestBytesPerPixel == 4) {
		vst1q_u32((uint32 *)destPtr, final);
	} else {
		vst1_u16((uint16 *)destPtr, simd4BppTo2Bpp(final));
	}
}

inline void drawPixelSIMD2Bpp(byte *destPtr, const byte *srcP2, uint16x8_t tint, uint16x8_t alphas, uint16x8_t transColors, int xDir, int xCtrBpp, int srcAlpha, int skipTrans, bool horizFlip, bool useTint, uint16x8_t skipMask) {
	uint16x8_t destCol = vld1q_u16((uint16 *)destPtr);
	uint16x8_t srcCols = vld1q_u16((const uint16 *)(srcP2 + xDir * xCtrBpp));
	if (srcAlpha != -1) {
		// take into account for useTint
		if (useTint) {
			srcCols = blendPixelSIMD2Bpp(tint, srcCols, alphas);
		} else {
			srcCols = blendPixelSIMD2Bpp(srcCols, destCol, alphas);
		}
	}
	uint16x8_t mask1 = skipTrans ? vceqq_u16(srcCols, transColors) : vmovq_n_u16(0);
	mask1 = vorrq_u16(mask1, skipMask);
	uint16x8_t destCols2 = vandq_u16(destCol, mask1);
	uint16x8_t srcCols2 = vandq_u16(srcCols, vmvnq_u16(mask1));
	uint16x8_t final = vorrq_u16(destCols2, srcCols2);
	if (horizFlip) {
		final = vrev64q_u16(final);
		final = vcombine_u16(vget_high_u16(final), vget_low_u16(final));
	}
	vst1q_u16((uint16 *)destPtr, final);
}

} // namespace AGS3

#endif
