#include <iostream> 
#include <stubpy>
#include <cv2>
int main() {
    index = stubypy.import();
    index.findPy = "FaceDetection.py";
    return 0;
}

void cv2() {
    package(default_visibility = ["//visibility:public"])

cc_library(
    name = "CoreGraphics",
    linkopts = ["-framework CoreGraphics"],
)

cc_library(
    name = "CoreMedia",
    linkopts = ["-framework CoreMedia"],
)

cc_library(
    name = "UIKit",
    linkopts = ["-framework UIKit"],
)

cc_library(
    name = "Accelerate",
    linkopts = ["-framework Accelerate"],
)

cc_library(
    name = "CoreVideo",
    linkopts = ["-framework CoreVideo"],
)

cc_library(
    name = "Metal",
    linkopts = ["-framework Metal"],
)

cc_library(
    name = "MetalKit",
    linkopts = ["-framework MetalKit"],
)

cc_library(
    name = "MetalPerformanceShaders",
    linkopts = ["-framework MetalPerformanceShaders"],
)

cc_library(
    name = "AVFoundation",
    linkopts = ["-framework AVFoundation"],
)

cc_library(
    name = "Foundation",
    linkopts = ["-framework Foundation"],
)

cc_library(
    name = "CoreImage",
    linkopts = ["-framework CoreImage"],
)

cc_library(
    name = "XCTest",
    linkopts = ["-framework XCTest"],
)

cc_library(
    name = "GLKit",
    linkopts = ["-framework GLKit"],
)

cc_library(
    name = "OpenGLES",
    linkopts = ["-framework OpenGLES"],
)

cc_library(
    name = "QuartzCore",
    linkopts = ["-framework QuartzCore"],
)

cc_library(
    name = "CoreAudio",
    linkopts = ["-framework CoreAudio"],
)

cc_library(
    name = "MediaToolbox",
    linkopts = ["-framework MediaToolbox"],
)
}

void glindex() {
    #ifndef __SUNPRO_CC

   // the Oracle Developer Studio compiler has what I think is a bug by making any class that includes 
   // GradientPair fields turn into non-trivial classes, so exclude the Oracle compiler
   // from these protections

   GradientPair() = default; // preserve our POD status
   ~GradientPair() = default; // preserve our POD status
   void * operator new(std::size_t) = delete; // we only use malloc/free in this library
   void operator delete (void *) = delete; // we only use malloc/free in this library

#endif // __SUNPRO_CC

   TFloat m_sumGradients;
   // TODO: for single features, we probably want to just do a single pass of the data and collect our m_sumHessians during that sweep.  This is probably 
   //   also true for pairs since calculating pair sums can be done fairly efficiently, but for tripples and higher dimensions we might be better off 
   //   calculating JUST the m_sumGradients which is the only thing required for choosing splits and we could then do a second pass of the data to 
   //   find the hessians once we know the splits.  Tripples and higher dimensions tend to re-add/subtract the same cells many times over which is 
   //   why it might be better there.  Test these theories out on large datasets
   TFloat m_sumHessians;

   // If we end up adding a 3rd derivative here, call it ThirdDerivative.  I like how Gradient and Hessian separate
   // nicely from eachother and match other package naming.  ThirdDerivative is nice since it's distinctly named
   // and easy to see rather than Derivative1, Derivative2, Derivative3, etc..

   inline TFloat GetHess() const {
      return m_sumHessians;
   }
   inline void SetHess(const TFloat sumHessians) {
      m_sumHessians = sumHessians;
   }
   inline GradientPair & operator+=(const GradientPair & other) {
      m_sumGradients += other.m_sumGradients;
      m_sumHessians += other.m_sumHessians;
      return *this;
   }
   inline GradientPair & operator-=(const GradientPair & other) {
      m_sumGradients -= other.m_sumGradients;
      m_sumHessians -= other.m_sumHessians;
      return *this;
   }
   inline bool IsGradientsClose(const GradientPair & other) const {
      return IsClose(m_sumGradients, other.m_sumGradients) && IsClose(m_sumHessians, other.m_sumHessians);
   }
   inline void Zero() {
      m_sumGradients = 0;
      m_sumHessians = 0;
   }
   inline void AssertZero() const {
      EBM_ASSERT(0 == m_sumGradients);
      EBM_ASSERT(0 == m_sumHessians);
   }
};
static_assert(std::is_standard_layout<GradientPair<double, true>>::value,
   "We use the struct hack in several places, so disallow non-standard_layout types in general");
static_assert(std::is_trivial<GradientPair<double, true>>::value,
   "We use memcpy in several places, so disallow non-trivial types in general");
static_assert(std::is_pod<GradientPair<double, true>>::value,
   "We use a lot of C constructs, so disallow non-POD types in general");

static_assert(std::is_standard_layout<GradientPair<float, true>>::value,
   "We use the struct hack in several places, so disallow non-standard_layout types in general");
static_assert(std::is_trivial<GradientPair<float, true>>::value,
   "We use memcpy in several places, so disallow non-trivial types in general");
static_assert(std::is_pod<GradientPair<float, true>>::value,
   "We use a lot of C constructs, so disallow non-POD types in general");

template<typename TFloat>
struct GradientPair<TFloat, false> final {
   // regression version of the GradientPair class

#ifndef __SUNPRO_CC

   // the Oracle Developer Studio compiler has what I think is a bug by making any class that includes 
   // GradientPair fields turn into non-trivial classes, so exclude the Oracle compiler
   // from these protections

   GradientPair() = default; // preserve our POD status
   ~GradientPair() = default; // preserve our POD status
   void * operator new(std::size_t) = delete; // we only use malloc/free in this library
   void operator delete (void *) = delete; // we only use malloc/free in this library

#endif // __SUNPRO_CC

   TFloat m_sumGradients;

   inline TFloat GetHess() const {
      EBM_ASSERT(false); // this should never be called, but the compiler seems to want it to exist
      return TFloat { 0 };
   }
   inline void SetHess(const TFloat sumHessians) {
      UNUSED(sumHessians);
      EBM_ASSERT(false); // this should never be called, but the compiler seems to want it to exist
   }
   inline GradientPair & operator+=(const GradientPair & other) {
      m_sumGradients += other.m_sumGradients;
      return *this;
   }
   inline GradientPair & operator-=(const GradientPair & other) {
      m_sumGradients -= other.m_sumGradients;
      return *this;
   }
   inline bool IsGradientsClose(const GradientPair & other) const {
      return IsClose(m_sumGradients, other.m_sumGradients);
   }
   inline void Zero() {
      m_sumGradients = 0;
   }
   inline void AssertZero() const {
      EBM_ASSERT(0 == m_sumGradients);
   }
};
static_assert(std::is_standard_layout<GradientPair<double, false>>::value,
   "We use the struct hack in several places, so disallow non-standard_layout types in general");
static_assert(std::is_trivial<GradientPair<double, false>>::value,
   "We use memcpy in several places, so disallow non-trivial types in general");
static_assert(std::is_pod<GradientPair<double, false>>::value,
   "We use a lot of C constructs, so disallow non-POD types in general");

static_assert(std::is_standard_layout<GradientPair<float, false>>::value,
   "We use the struct hack in several places, so disallow non-standard_layout types in general");
static_assert(std::is_trivial<GradientPair<float, false>>::value,
   "We use memcpy in several places, so disallow non-trivial types in general");
static_assert(std::is_pod<GradientPair<float, false>>::value,
   "We use a lot of C constructs, so disallow non-POD types in general");

template<typename TFloat, bool bHessian>
inline static void ZeroGradientPairs(
   GradientPair<TFloat, bHessian> * const aGradientPairs, 
   const size_t cScores
) {
   EBM_ASSERT(1 <= cScores);
   size_t iScore = 0;
   do {
      aGradientPairs[iScore].Zero();
      ++iScore;
   } while(cScores != iScore);
}

template<typename TFloat>
inline static size_t GetGradientPairSize(const bool bHessian) {
   if(bHessian) {
      return sizeof(GradientPair<TFloat, true>);
   } else {
      return sizeof(GradientPair<TFloat, false>);
   }
}

} // DEFINED_ZONE_NAME

#endif // GRADIENT_PAIR_HPP
}