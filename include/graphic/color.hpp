#pragma once

#include <Eigen/Core>

using Color = Eigen::Vector3f;

using Color4f = Eigen::Vector3f;

namespace ColorPreset
{

inline const Color red{1.0f, 0.0f, 0.0f};
inline const Color green{0.0f, 1.0f, 0.0f};
inline const Color blue{0.0f, 0.0f, 1.0f};

inline const Color yellow{1.0f, 1.0f, 0.0f};
inline const Color skyblue{0.0f, 1.0f, 1.0f};
inline const Color pink{1.0f, 0.0f, 1.0f};

inline const Color black{0.0f, 0.0f, 0.0f};
inline const Color white{1.0f, 1.0f, 1.0f};
inline const Color light_gray{0.9f, 0.9f, 0.9f};
inline const Color dark_gray{0.2f, 0.2f, 0.2f};

}  // namespace ColorPreset
