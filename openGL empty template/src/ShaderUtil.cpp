#include "ShaderUtil.h"
#include <fstream>
#include <sstream>

using namespace std;

GLuint ShaderUtil::createProgam (const string& pVertexShaderPath, const string& pFragmentShaderPath) {
	//load the shaders
    GLuint vertexShader = _loadShader(pVertexShaderPath, GL_VERTEX_SHADER);
    GLuint fragmentShader = _loadShader(pFragmentShaderPath, GL_FRAGMENT_SHADER);

	//print the shader handles
    cout << "VS ID:" << vertexShader << endl;
    cout << "FS ID:" << fragmentShader << endl;

	//exit program creation if one or both of the shaders didn't compile correctly
    if (vertexShader == 0 || fragmentShader == 0) {
        cout << "One or more shaders failed, exiting..." << endl;
        return 0;
    }

	//add the shaders to a vector
    std::vector<GLuint> shaders;
    shaders.push_back(vertexShader);
    shaders.push_back(fragmentShader);

	//create program by compiling vector of shaders
    GLuint program = _compileAndLinkProgram(shaders);

	//delete the shader (we already have them in a program)
    for (size_t i = 0; i < shaders.size(); i++) {
        glDeleteShader (shaders[i]);
    }

    cout << "Program id:" << program << endl;
    return program;
}


GLuint ShaderUtil::_loadShader (const string& pShaderPath, GLenum pShaderType) {
    cout << endl << endl;
	//read the file by putting it in a stream
    ifstream sourceFile (pShaderPath.c_str());
    if (!sourceFile) {
        cout << "Could not read shader file <" << pShaderPath << ">";
        return 0;
    }
	//dump content from ifstream to stringstream 
    stringstream buffer;
    buffer << sourceFile.rdbuf();
    sourceFile.close();

	//dump code in console
    cout << "SHADER:" << pShaderPath << endl;
    cout << "-----------------------------------" << endl;
    string source = buffer.str();
    cout << source;
    cout << "-----------------------------------" << endl;
    cout << "Shader source successfully loaded..." << endl << endl;

	//create empty shader by type
    cout << "Creating shader object..." << endl;
    GLuint shaderHandle = glCreateShader(pShaderType);
    cout << "Shader creation successfull?" << (shaderHandle != 0) << endl;
    if (shaderHandle == 0) return 0;

	//loading read shader code into the actual shader object
    cout << "Loading source into shader..." << endl;
    char const * sourcePointer = source.c_str();
    //question: why NULL?
	//answer  : the 4th parameter represents string length. if the param == null, the string will be null terminated
	//		    this is to make sure that the shader doesn't read past the end of the data of the source string memory
    glShaderSource (shaderHandle, 1, &sourcePointer, NULL);
	
	//compile the shader
    cout << "Compiling shader..." << endl;
    glCompileShader (shaderHandle);
    GLint compileStatus = 0;
    glGetShaderiv (shaderHandle, GL_COMPILE_STATUS, &compileStatus); //get compile status
    if (compileStatus == GL_FALSE) {
        cout << "Compilation failed:" << endl;

        GLint logLength = 0;
        glGetShaderiv (shaderHandle, GL_INFO_LOG_LENGTH, &logLength); //get log length
        if (logLength > 0) {
            GLchar* errorLog = new GLchar[logLength];
            glGetShaderInfoLog (shaderHandle, logLength, NULL, errorLog); //parse log into errorlog
            cout << errorLog << endl;
            delete [] errorLog;
        } else {
            cout << "No info available." << endl;
        }
        return 0;
    }

	//return the shader handle
    cout << "Compilation succesful." << endl << endl;
    return shaderHandle;
}

/**
 * Take the given list of shaders and link them into a new program
 */
GLuint ShaderUtil::_compileAndLinkProgram (const std::vector<GLuint> &pShaders) {
    
	//create program handle
	cout << "Creating new program..." << endl;
    GLuint program = glCreateProgram(); 

	//attach shaders
    cout << "Attaching all shaders..." << endl;
    for (size_t i = 0; i < pShaders.size(); i++) {
        glAttachShader (program, pShaders[i]);
    }

	//link the program
    cout << "Linking program..." << endl;
    glLinkProgram (program);


	//check for any errors linking the program
    int linkStatus = 0;
    glGetProgramiv (program, GL_LINK_STATUS, &linkStatus);

    if (linkStatus == GL_FALSE) {
        cout << "Linking failed... " << endl;

        int linkLogSize = 0;
        glGetProgramiv (program, GL_INFO_LOG_LENGTH, &linkLogSize);

        GLchar* linkLog = new GLchar[linkLogSize];
        glGetProgramInfoLog (program, linkLogSize, NULL, linkLog);
        cout << linkLog << endl;
        delete [] linkLog;
        return 0;

    } else {
        cout << "Link successfull." << endl;
    }

    //detach the shaders again (we have a binary linked program now)
    for (size_t i = 0; i < pShaders.size(); i++) {
        glDetachShader (program, pShaders[i]);
    }

    return program;
}

