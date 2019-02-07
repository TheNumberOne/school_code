#pragma once

class AppState {
public:
    virtual ~AppState() = default;

    virtual std::array<glm::vec3, 36> bigSquareColors() = 0;

    virtual std::array<glm::vec3, 16> littleSquareColors() = 0;

    virtual glm::mat4 getCamera() = 0;

    virtual std::unique_ptr<AppState> nextState() = 0;
};

class InitialAppState : public AppState {
public:
    InitialAppState();
    ~InitialAppState() override = default;

    std::array<glm::vec3, 36> bigSquareColors() override {
        return m_bigSquareColors;
    }

    std::array<glm::vec3, 16> littleSquareColors() override {
        return m_littleSquareColors;
    }

    glm::mat4 getCamera() override;

    std::unique_ptr<AppState> nextState() override;

private:
    std::array<glm::vec3, 36> m_bigSquareColors;
    std::array<glm::vec3, 16> m_littleSquareColors;
};

class SecondAppState : public InitialAppState {
public:
    ~SecondAppState() override = default;

    glm::mat4 getCamera() override;
    std::unique_ptr<AppState> nextState() override;
};

class ThirdAppState : public SecondAppState {
public:
    ThirdAppState();
    ~ThirdAppState() override = default;

    std::array<glm::vec3, 36> bigSquareColors() override {
        return m_bigSquareColors;
    }

    std::array<glm::vec3, 16> littleSquareColors() override {
        return m_littleSquareColors;
    }

    std::unique_ptr<AppState> nextState() override;

private:
    std::array<glm::vec3, 36> m_bigSquareColors;
    std::array<glm::vec3, 16> m_littleSquareColors;
};

class FourthAppState : public ThirdAppState {
public:
    ~FourthAppState() override = default;

    glm::mat4 getCamera() override;
};