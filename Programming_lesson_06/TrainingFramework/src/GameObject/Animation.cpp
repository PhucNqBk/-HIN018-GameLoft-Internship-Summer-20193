#include "Animation.h"
#include "Shaders.h"
#include "Texture.h"
#include "Models.h"

Animation::Animation(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, int row, int col, float frtime) :
	Sprite2D(model, shader, texture), m_RowCount(row), m_ColCount(col), m_CurrentFrame(0), m_FrameTime(frtime), m_CurrentTime(0.0), m_IsLoop(true)
{
	SetSize(48, 96);
}
Animation::~Animation()
{

}
void Animation::Init()
{
	Sprite2D::Init();
}
void Animation::Draw()
{
	glUseProgram(m_pShader->program);
	glBindBuffer(GL_ARRAY_BUFFER, m_pModel->GetVertexObject());
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_pModel->GetIndiceObject());

	GLuint iTempShaderVaribleGLID = -1;
	Matrix matrixWVP;

	matrixWVP = m_WorldMat;//* m_pCamera->GetLookAtCamera();

	if (m_pTexture != nullptr)
	{
		glActiveTexture(GL_TEXTURE0);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, m_pTexture->Get2DTextureAdd());
		if (m_pShader->iTextureLoc[0] != -1)
			glUniform1i(m_pShader->iTextureLoc[0], 0);
	}
	


	iTempShaderVaribleGLID = -1;
	iTempShaderVaribleGLID = m_pShader->GetAttribLocation((char*)"a_posL");
	if (iTempShaderVaribleGLID != -1)
	{
		glEnableVertexAttribArray(iTempShaderVaribleGLID);
		glVertexAttribPointer(iTempShaderVaribleGLID, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), VETEX_POSITION);
	}

	iTempShaderVaribleGLID = -1;
	iTempShaderVaribleGLID = m_pShader->GetAttribLocation((char*) "a_uv");
	if (iTempShaderVaribleGLID != -1)
	{
		glEnableVertexAttribArray(iTempShaderVaribleGLID);
		glVertexAttribPointer(iTempShaderVaribleGLID, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), VETEX_UV);
	}


	iTempShaderVaribleGLID = -1;
	iTempShaderVaribleGLID = m_pShader->GetUniformLocation((char*)"u_matMVP");
	if (iTempShaderVaribleGLID != -1)
		glUniformMatrix4fv(iTempShaderVaribleGLID, 1, GL_FALSE, matrixWVP.m[0]);

	iTempShaderVaribleGLID = -1;
	iTempShaderVaribleGLID = m_pShader->GetUniformLocation((char*)"u_row");
	if (iTempShaderVaribleGLID != -1)
		glUniform1f(iTempShaderVaribleGLID, (float)m_RowCount);

	iTempShaderVaribleGLID = -1;
	iTempShaderVaribleGLID = m_pShader->GetUniformLocation((char*)"u_col");
	if (iTempShaderVaribleGLID != -1)
		glUniform1f(iTempShaderVaribleGLID, (float)m_ColCount);

	iTempShaderVaribleGLID = -1;
	iTempShaderVaribleGLID = m_pShader->GetUniformLocation((char*)"u_curr_row");
	if (iTempShaderVaribleGLID != -1)
		glUniform1f(iTempShaderVaribleGLID, (float)(m_IDs[m_CurrentFrame] / m_ColCount));

	iTempShaderVaribleGLID = -1;
	iTempShaderVaribleGLID = m_pShader->GetUniformLocation((char*)"u_curr_col");
	if (iTempShaderVaribleGLID != -1)
		glUniform1f(iTempShaderVaribleGLID, (float)(m_IDs[m_CurrentFrame] % m_ColCount));

	glDrawElements(GL_TRIANGLES, m_pModel->GetNumIndiceObject(), GL_UNSIGNED_INT, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
}
void Animation::Update(GLfloat deltatime)
{
	m_CurrentTime += deltatime;
	if (m_CurrentTime > m_FrameTime) {
		m_CurrentFrame++;
		if (m_CurrentFrame >= m_FrameCount ) {
			m_CurrentFrame = 0;
		}
		
		m_CurrentTime -= m_FrameTime;
	}
}
void Animation::Update(GLfloat deltatime, bool isInvunerable)
{
	m_CurrentTime += deltatime;
	if (m_CurrentTime > m_FrameTime) {
		m_CurrentFrame++;
		if (m_CurrentFrame >= m_FrameCount) {
			m_CurrentFrame = 0;
		}

		m_CurrentTime -= deltatime;
	}
}
void Animation::SetIDs(const int a[], int count)
{
	m_IDs.clear();
	std::vector<int>().swap(m_IDs);
	for (int i = 0; i < count; ++i) {
		m_IDs.push_back(a[i]);
	}
	m_FrameCount = count;
}
void Animation::SetIDs( std::vector<int> a)
{
	m_IDs.clear();
	std::vector<int>().swap(m_IDs);
	m_IDs = a;
	m_FrameCount = a.size();
}
void Animation::SetIsLoop(bool loop)
{
	m_IsLoop = loop;
}
int	Animation::GetCurrentFrame()
{
	return m_CurrentFrame;
}
int	Animation::GetFrameCount()
{
	return m_FrameCount;
}