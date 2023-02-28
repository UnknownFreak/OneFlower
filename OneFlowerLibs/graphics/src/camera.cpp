
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

    const glm::vec3& Camera::getPosition()
    {
        return mPosition;
    }

    const glm::vec3& Camera::getRotation()
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
        mProjectionMatrix = glm::perspective(mFov, mWidth / mHeight, 0.01F, 100.0F);
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
        mProjectionMatrix = glm::ortho(0.f, mWidth, 0.f, mHeight, 0.01f, 100.f);
    }

#pragma endregion

}