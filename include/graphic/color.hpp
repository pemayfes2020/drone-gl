#pragma once

#include <Eigen/Core>

using Color = Eigen::Vector3d;

using Color4d = Eigen::Vector3d;

namespace ColorPreset
{

inline const Color red{1.0, 0.0, 0.0};
inline const Color green{0.0, 1.0, 0.0};
inline const Color blue{0.0, 0.0, 1.0};

inline const Color yellow{1.0, 1.0, 0.0};
inline const Color skyblue{0.0, 1.0, 1.0};
inline const Color pink{1.0, 0.0, 1.0};

inline const Color black{0.0, 0.0, 0.0};
inline const Color white{1.0, 1.0, 1.0};
inline const Color light_gray{0.9, 0.9, 0.9};
inline const Color dark_gray{0.2, 0.2, 0.2};

}  // namespace ColorPreset
