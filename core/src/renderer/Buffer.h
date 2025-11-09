#pragma once

#include <iostream>
#include <vector>
#include <string>

#include "Utils.h"

namespace Renderer {

  enum class DrawType : uint8_t
  {
    StreamDraw = 0, StaticDraw, DynamicDraw
  };

  enum class DataType : uint8_t
  {
    Float = 0, Float2, Float3, Float4,
    Mat3, Mat4,
    Int, Int2, Int3, Int4,
    Boolean
  };

  static uint32_t dataTypeSize(DataType type)
  {
    switch (type)
    {
    case DataType::Float:   return 4;
    case DataType::Float2:  return 4 * 2;
    case DataType::Float3:  return 4 * 3;
    case DataType::Float4:  return 4 * 4;
    case DataType::Mat3:    return 4 * 3 * 3;
    case DataType::Mat4:    return 4 * 4 * 4;
    case DataType::Int:     return 4;
    case DataType::Int2:    return 4 * 2;
    case DataType::Int3:    return 4 * 3;
    case DataType::Int4:    return 4 * 4;
    case DataType::Boolean:    return 1;
    }

    Log::Assert(false, "Unknown DataType passed to dataTypeSize()!");
    return 0;
  }

  struct BufferElement
  {
    std::string name;
    DataType type;
    uint32_t size;
    uint64_t offset;
    bool normalized;

    BufferElement(DataType type, const std::string& name, bool normalized = false)
      : name(name), type(type), size(dataTypeSize(type)), offset(0), normalized(normalized) {
    }

    uint32_t getComponentCount() const
    {
      switch (type)
      {
      case DataType::Float:   return 1;
      case DataType::Float2:  return 2;
      case DataType::Float3:  return 3;
      case DataType::Float4:  return 4;
      case DataType::Mat3:    return 3 * 3;
      case DataType::Mat4:    return 4 * 4;
      case DataType::Int:     return 1;
      case DataType::Int2:    return 2;
      case DataType::Int3:    return 3;
      case DataType::Int4:    return 4;
      case DataType::Boolean:    return 1;
      }

      Log::Assert(false, "Unknown DataType in getComponentCount()!");
      return 0;
    }
  };

  class BufferLayout
  {
  public:
    BufferLayout() {};

    BufferLayout(const std::initializer_list<BufferElement>& elements)
      : m_elements(elements)
    {
      calculateOffsetAndStride();
    }

    inline uint32_t getStride() const { return m_stride; }
    inline std::vector<BufferElement> getElements() const { return m_elements; }

    inline const std::vector<BufferElement>::iterator begin() { return m_elements.begin(); }
    inline const std::vector<BufferElement>::iterator end() { return m_elements.end(); }
    inline const std::vector<BufferElement>::const_iterator begin() const { return m_elements.begin(); }
    inline const std::vector<BufferElement>::const_iterator end() const { return m_elements.end(); }
  private:
    void calculateOffsetAndStride()
    {
      uint64_t offset = 0;
      m_stride = 0;

      for (BufferElement& element : m_elements)
      {
        element.offset = offset;
        offset += element.size;
        m_stride += element.size;
      }
    }
  private:
    std::vector<BufferElement> m_elements;
    uint32_t m_stride = 0;
  };

  class VertexBuffer
  {
  public:
    virtual ~VertexBuffer() {};

    virtual void bind() const = 0;
    virtual void unbind() const = 0;

    virtual void sendData(float* vertices, uint32_t size) const = 0;

    virtual inline const BufferLayout& getLayout() const = 0;
    virtual inline void setLayout(BufferLayout layout) = 0;

    static VertexBuffer* create(const std::initializer_list<float>& vertices);
    static VertexBuffer* create(float* vertices, uint32_t size);
  };

  class IndexBuffer
  {
  public:
    virtual ~IndexBuffer() {};

    virtual void bind() const = 0;
    virtual void unbind() const = 0;

    virtual void set(uint32_t* indices, uint32_t size) const = 0;
    
    virtual inline uint32_t getCount() const = 0;

    static IndexBuffer* create(const std::initializer_list<uint32_t>& indices);
    static IndexBuffer* create(uint32_t* indices, uint32_t size);
  };

}