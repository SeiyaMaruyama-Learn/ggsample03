#include "gg.h"
using namespace gg;

#include "object.h"

//
// ���_�z��I�u�W�F�N�g�̍쐬
//
//   vertices: ���_��
//   position: ���_�̓񎟌��ʒu (GLfloat[3] �̔z��)
//   lines: ������
//   index: �����̒��_�C���f�b�N�X
//   �߂�l: �쐬���ꂽ���_�z��I�u�W�F�N�g��
//
GLuint createObject(GLuint vertices, const GLfloat (*position)[3], GLuint lines, const GLuint *index)
{
  // ���_�z��I�u�W�F�N�g
  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  // ���_�o�b�t�@�I�u�W�F�N�g
  GLuint vbo;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof (GLfloat[3]) * vertices, position, GL_STATIC_DRAW);

  // �C���f�b�N�X�o�b�t�@�I�u�W�F�N�g
  GLuint ibo;
  glGenBuffers(1, &ibo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof (GLuint) * lines, index, GL_STATIC_DRAW);

  // ��������Ă��钸�_�o�b�t�@�I�u�W�F�N�g�� in �ϐ�����Q�Ƃł���悤�ɂ���
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(0);

  // ���_�z��I�u�W�F�N�g�̌���������������ɒ��_�o�b�t�@�I�u�W�F�N�g�ƃC���f�b�N�X�o�b�t�@�I�u�W�F�N�g�̌�������������
  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  

  return vao;
}
