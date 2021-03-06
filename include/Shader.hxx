#ifndef OPENGL_PBR_SHADER_HXX
#define OPENGL_PBR_SHADER_HXX

#include <GL/glew.h>

#include <fstream>
#include <glm/glm.hpp>
#include <string>
#include <unordered_map>
#include <vector>

struct PointLightContext
{
    PointLightContext()
        : uniformColor{ 0 }
        , uniformAmbientIntensity{ 0 }
        , uniformDiffuseIntensity{ 0U }
        , uniformPosition{ 0U }
        , uniformConstant{ 0U }
        , uniformLinear{ 0U }
        , uniformExponent{ 0U }
    {
    }
    std::uint32_t uniformColor;
    std::uint32_t uniformAmbientIntensity;
    std::uint32_t uniformDiffuseIntensity;
    std::uint32_t uniformPosition;
    std::uint32_t uniformConstant;
    std::uint32_t uniformLinear;
    std::uint32_t uniformExponent;
};

struct SpotLightContext : public PointLightContext
{
    SpotLightContext()  //
        : PointLightContext{}
        , uniformDirection{ 0U }
        , uniformEdge{ 0U }
    {
    }
    std::uint32_t uniformDirection;
    std::uint32_t uniformEdge;
};

class SpotLight;
class Shader
{
    enum class ShaderType : GLenum
    {
        FRAGMENT = GL_FRAGMENT_SHADER,
        VERTEX   = GL_VERTEX_SHADER,
        GEOMETRY = GL_GEOMETRY_SHADER
    };

public:
    Shader(const char* vertexShader, const char* fragmentShader);
    ~Shader();

    void createShaderFromString(const char* vertexShader, const char* fragmentShader);
    void createShaderFromFile(const char* vertexShader, const char* fragmentShader);

    void updateGlUniformMat4(const char* uniformName, std::uint32_t count, bool transpose, glm::mat4& value);
    void updateGlUniform3f(const char* uniformName, glm::vec3& values);
    void updateGlUniform1f(const char* uniformName, float& value);
    void updateGlUniform1i(const char* uniformName, std::uint32_t& value);

    void updateGlUniform3f(std::uint32_t location, glm::vec3& value);
    void updateGlUniform1f(std::uint32_t location, float& value);
    void updateGlUniformMat4(std::uint32_t location, std::uint32_t count, bool transpose, glm::mat4& value);
    void updateGlUniform1i(std::uint32_t location, std::uint32_t& value);

    PointLightContext& getPointLightContext(int index);
    SpotLightContext&  getSpotLightContext(int index);

    void useShader();
    void clearShader();
    void useSpotLight(SpotLight* lights, unsigned int size);
protected:
    void        compileShader(const char* vertexShader, const char* fragmentShader);
    void        addShader(std::uint32_t theProgram, const char* shaderCode, ShaderType shaderType);
    std::string readFile(const char* fileLocation);

    std::uint32_t getUniformLocation(const char* uniformName) const;

private:
    std::uint32_t                  mShaderID;
    std::vector<PointLightContext> mPointLightsContexts;
    std::vector<SpotLightContext>  mSpotLightContexts;

    mutable std::unordered_map<std::string, std::uint32_t> mUniformCache;
};

#endif  // OPENGL_PBR_SHADER_HXX
