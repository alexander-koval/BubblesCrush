// uniform mat4 u_mvpMatrix;
// attribute vec4 a_position;
// attribute vec2 a_texCoord;
// varying vec2 v_texCoord;

void main()
{
        gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
        gl_TexCoord[0] = gl_MultiTexCoord0;

        //   gl_Position = u_mvpMatrix * a_position;
        //   gl_TexCoord[0] = gl_MultiTexCoord0;
        //	a_texCoord = gl_MultiTexCoord0;
        //    v_texCoord = a_texCoord;

}
