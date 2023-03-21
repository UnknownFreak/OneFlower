#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>

namespace of::graphics::view
{

    class Camera
    {
    protected:
        float mFov;
        float mWidth;
        float mHeight;

        glm::mat4 mProjectionMatrix;
        glm::mat4 mViewMatrix;
        glm::mat4 mProjView;

        glm::vec3 mPosition;
        glm::vec3 mRotation;

        virtual void recalculatePerspective() = 0;
        virtual void recalculateViewProj();

    protected:

        void initCamera();

    public:
        Camera(float fov, float width, float height);
        virtual ~Camera() = default;
        void changeFov(float fov);
        void changeAspect(float width, float height);

        void setPosition(glm::vec3 pos);
        void setRotation(glm::vec3 pos);

        void lookAt(glm::vec3 pos, glm::vec3 dir, glm::vec3 up = glm::vec3(0.0F, 1.0F, 0.0F));
        void lookAt(glm::mat4& mView);

        const glm::vec3& getPosition();
        const glm::vec3& getRotation();

        const glm::mat4& getView() const;
        const glm::mat4& getProjection() const;

        const glm::mat4& getViewProjection() const;
    };

    class OrthographicCamera : public Camera
    {
    public:
        OrthographicCamera(float width, float height);
        ~OrthographicCamera();

    private:
        virtual void recalculatePerspective() override;
;
    };

    class PerspectiveCamera : public Camera
    {
    public:
        PerspectiveCamera(float fov, float width, float height);
        ~PerspectiveCamera();

    private:
        virtual void recalculatePerspective() override;
    };
}

#endif