
#if defined(_WIN32)
#pragma warning(push)
#pragma warning(disable : 4127)
#pragma warning(disable : 4251)
#pragma warning(disable : 4201)
#endif
#define GLM_FORCE_INLINE
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#if defined(_WIN32)
#pragma warning(pop)
#endif

#include <graphics/view/camera.hpp>
#include <algorithm>

namespace of::graphics::view
{

#pragma region camera
    Camera::Camera(float fov, float width, float height)
        : mFov(fov)
        , mWidth(width)
        , mHeight(height)
        , mProjectionMatrix()
        , mViewMatrix(1.0F)
        , mProjView(1.0F)
        , mPosition(0.0F)
        , mRotation(0.0F)
        , mNear(0.01f)
        , mFar(100.f)
    {
    }

    void Camera::changeFov(float fov)
    {
        mFov = fov;
        recalculatePerspective();
    }

    void Camera::changeAspect(float width, float height)
    {
        if ((width != 0.0F) && (height != 0.0F))
        {
            mWidth = width;
            mHeight = height;
            recalculatePerspective();
        }
    }

    void Camera::setPosition(glm::vec3 pos)
    {
        mPosition = pos;
        recalculateViewProj();
    }

    void Camera::setRotation(glm::vec3 rot)
    {
        mRotation = rot;
        recalculateViewProj();
    }

    void Camera::lookAt(glm::vec3 pos, glm::vec3 dir, glm::vec3 up)
    {
        mViewMatrix = glm::lookAt(pos, dir, up);
    }

    void Camera::lookAt(glm::mat4& mView)
    {
        mViewMatrix = mView;
    }

    const glm::vec3& Camera::getPosition() const
    {
        return mPosition;
    }

    const glm::vec3& Camera::getRotation() const
    {
        return mRotation;
    }

    const glm::mat4& Camera::getView() const
    {
        return mViewMatrix;
    }

    const glm::mat4& Camera::getProjection() const
    {
        return mProjectionMatrix;
    }

    const glm::mat4& Camera::getViewProjection() const
    {
        return mProjView;
    }

    void Camera::recalculateViewProj()
    {
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), mPosition);
        glm::mat4 rot = glm::yawPitchRoll(mRotation.z, mRotation.x, mRotation.y);

        mViewMatrix = glm::inverse(transform * rot);
        mProjView = mProjectionMatrix * mViewMatrix;
    }

    void Camera::initCamera()
    { 
        recalculatePerspective();
        recalculateViewProj();
    }

#pragma endregion
#pragma region PerspectiveCamera

    PerspectiveCamera::PerspectiveCamera(float fov, float width, float height) : Camera(fov, width, height)
    {
        initCamera();
    }

    PerspectiveCamera::~PerspectiveCamera() {}

    void PerspectiveCamera::recalculatePerspective()
    {
        mProjectionMatrix = glm::perspective(mFov, mWidth / mHeight, mNear, mFar);
    }

    glm::vec3 PerspectiveCamera::projectRayFromCursor(const float cursorX, const float cursorY) const
    {
        return projectRayNDC(
            (2.f * cursorX) / mWidth - 1,
            1.f - (2.f * cursorY) / mHeight);
    }

    glm::vec3 PerspectiveCamera::projectRayNDC(const float x, const float y) const
    {
        float nx = std::clamp(x, -1.f, 1.f);
        float ny = std::clamp(y, -1.f, 1.f);
            
        float z = 1.f;

        glm::vec3 ray_nds(nx, ny, z);
        glm::vec4 clip(nx, ny, -1.f, 1.f);
        glm::vec4 eye(glm::inverse(mProjectionMatrix) * clip);
        eye.z = -1.f;
        eye.w = 0.f;

        glm::vec4 inv_world(glm::inverse(mViewMatrix) * eye);
        glm::vec3 world(inv_world.x, inv_world.y, inv_world.z);
       
        auto norm = glm::normalize(world);
        if (std::isfinite(norm.x) == false)
        {
            norm.x = 0.f;
        }
        return glm::normalize(world);
    }

#pragma endregion
#pragma region OrthoCamera

    OrthographicCamera::OrthographicCamera(float width, float height) : Camera(0.f, width, height)
    {
        initCamera();
    }

    OrthographicCamera::~OrthographicCamera()
    {
    }

    void OrthographicCamera::recalculatePerspective()
    {
        mProjectionMatrix = glm::ortho(0.f, mWidth, 0.f, mHeight, mNear, mFar);
    }

#pragma endregion

}