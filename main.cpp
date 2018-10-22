// �E�B���h�E�֘A�̏���
#include "Window.h"

// �V�F�[�_�[�֘A�̏���
#include "shader.h"

// �I�u�W�F�N�g�֘A�̏���
#include "object.h"

//
// �P�ʍs���ݒ肷��
//
//   m: �P�ʍs����i�[����z��
//
static void loadIdentity(GLfloat *m)
{
  m[ 0] = m[ 5] = m[10] = m[15] = 1.0f;
  m[ 1] = m[ 2] = m[ 3] = m[ 4] =
  m[ 6] = m[ 7] = m[ 8] = m[ 9] =
  m[11] = m[12] = m[13] = m[14] = 0.0f;
}

//
// ���𓊉e�ϊ��s������߂�
//
//   m: ���𓊉e�ϊ��s����i�[����z��
//   left, right: �r���[�{�����[���̍��E�[
//   bottom, top: �r���[�{�����[���̏㉺�[
//   zNear, zFar: �O���ʂ���ь���ʂ܂ł̋���
//
static void ortho(GLfloat *m, float left, float right, float bottom, float top, float zNear, float zFar)
{
  m[ 0] =  2.0f / (right - left);
  m[ 5] =  2.0f / (top - bottom);
  m[10] = -2.0f / (zFar - zNear);
  m[12] = -(right + left) / (right - left);
  m[13] = -(top + bottom) / (top - bottom);
  m[14] = -(zFar + zNear) / (zFar - zNear);
  m[15] =  1.0f;
  m[ 1] = m[ 2] = m[ 3] = m[ 4] = m[ 6] = m[ 7] = m[ 8] = m[ 9] = m[11] = 0.0f;
}

//
// �������e�ϊ��s������߂�
//
//   m: �������e�ϊ��s����i�[����z��
//   left, right: �O���ʂ̍��E�[
//   bottom, top: �O���ʂ̏㉺�[
//   zNear, zFar: �O���ʂ���ь���ʂ܂ł̋���
//
static void frustum(GLfloat *m, float left, float right, float bottom, float top, float zNear, float zFar)
{
  m[ 0] =  2.0f * zNear / (right - left);
  m[ 5] =  2.0f * zNear / (top - bottom);
  m[ 8] =  (right + left) / (right - left);
  m[ 9] =  (top + bottom) / (top - bottom);
  m[10] = -(zFar + zNear) / (zFar - zNear);
  m[11] = -1.0f;
  m[14] = -2.0f * zFar * zNear / (zFar - zNear);
  m[ 1] = m[ 2] = m[ 3] = m[ 4] = m[ 6] = m[ 7] = m[12] = m[13] = m[15] = 0.0f;
}

//
// ��p���w�肵�ē������e�ϊ��s������߂�
//
//   m: �������e�ϊ��s����i�[����z��
//   fovy: ��p�i���W�A���j
//   aspect: �E�B���h�E�̏c����
//   zNear, zFar: �O���ʂ���ь���ʂ܂ł̋���
//
static void perspective(GLfloat *m, float fovy, float aspect, float zNear, float zFar)
{
  // �y�h��z�������𓚂��Ă��������iloadIdentity() ��u�������Ă��������j
  loadIdentity(m);
}

//
// �r���[�ϊ��s������߂�
//
//   m: �r���[�ϊ��s����i�[����z��
//   ex, ey, ez: ���_�̈ʒu
//   tx, ty, tz: �ڕW�_�̈ʒu
//   ux, uy, uz: ������̃x�N�g��
//
static void lookat(GLfloat *m, float ex, float ey, float ez, float tx, float ty, float tz, float ux, float uy, float uz)
{
  // �y�h��z�������𓚂��Ă��������iloadIdentity() ��u�������Ă��������j
  loadIdentity(m);
}

//
// 4 �s 4 ��̍s��̐ς����߂�
//
//   m �� m1 �~ m2
//
static void multiply(GLfloat *m, const GLfloat *m1, const GLfloat *m2)
{
  for (int i = 0; i < 16; ++i)
  {
    int j = i & 3, k = i & ~3;

    // �z��ϐ��ɍs�񂪓]�u���ꂽ��ԂŊi�[����Ă��邱�Ƃ��l�����Ă���
    m[i] = m1[0 + j] * m2[k + 0] + m1[4 + j] * m2[k + 1] + m1[8 + j] * m2[k + 2] + m1[12 + j] * m2[k + 3];
  }
}

//
// ���C���v���O����
//
int main()
{
  // �E�B���h�E���쐬����
  Window window("ggsample03");

  // �w�i�F���w�肷��
  glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

  // �v���O�����I�u�W�F�N�g�̍쐬
  const GLuint program(loadProgram("simple.vert", "pv", "simple.frag", "fc"));

  // uniform �ϐ��̃C���f�b�N�X�̌����i������Ȃ���� -1�j
  const GLint mcLoc(glGetUniformLocation(program, "mc"));

  // �r���[�ϊ��s��� mv �ɋ��߂�
  GLfloat mv[16];
  lookat(mv, 3.0f, 4.0f, 5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

  // ���_����
  static const GLfloat position[][3] =
  {
    { -0.9f, -0.9f, -0.9f },  // (0)
    {  0.9f, -0.9f, -0.9f },  // (1)
    {  0.9f, -0.9f,  0.9f },  // (2)
    { -0.9f, -0.9f,  0.9f },  // (3)
    { -0.9f,  0.9f, -0.9f },  // (4)
    {  0.9f,  0.9f, -0.9f },  // (5)
    {  0.9f,  0.9f,  0.9f },  // (6)
    { -0.9f,  0.9f,  0.9f },  // (7)
  };
  static const int vertices(sizeof position / sizeof position[0]);

  // ���_�C���f�b�N�X
  static const GLuint index[] =
  {
    0, 1,
    1, 2,
    2, 3,
    3, 0,
    0, 4,
    1, 5,
    2, 6,
    3, 7,
    4, 5,
    5, 6,
    6, 7,
    7, 4,
  };
  static const GLuint lines(sizeof index / sizeof index[0]);

  // ���_�z��I�u�W�F�N�g�̍쐬
  const GLuint vao(createObject(vertices, position, lines, index));

  // �E�B���h�E���J���Ă���ԌJ��Ԃ�
  while (window.shouldClose() == GL_FALSE)
  {
    // �E�B���h�E����������
    glClear(GL_COLOR_BUFFER_BIT);

    // �V�F�[�_�v���O�����̎g�p�J�n
    glUseProgram(program);

    // ���e�ϊ��s�� mp �����߂� (window.getAspect() �̓E�B���h�E�̏c����)
    GLfloat mp[16];
    perspective(mp, 0.5f, window.getAspect(), 1.0f, 15.0f);

    // ���e�ϊ��s�� mp �ƃr���[�ϊ��s�� mv �̐ς�ϊ��s�� mc �ɋ��߂�
    GLfloat mc[16];
    multiply(mc, mp, mv);

    // uniform �ϐ� mc �ɕϊ��s�� mc ��ݒ肷��
    // �y�h��z�������𓚂��Ă��������iuniform �ϐ� mc �̃C���f�b�N�X�͕ϐ� mcLoc �ɓ����Ă��܂��j

    // �`��Ɏg�����_�z��I�u�W�F�N�g�̎w��
    glBindVertexArray(vao);

    // �}�`�̕`��
    glDrawElements(GL_LINES, lines, GL_UNSIGNED_INT, 0);

    // ���_�z��I�u�W�F�N�g�̎w�����
    glBindVertexArray(0);

    // �V�F�[�_�v���O�����̎g�p�I��
    glUseProgram(0);

    // �J���[�o�b�t�@�����ւ��ăC�x���g�����o��
    window.swapBuffers();
  }
}
