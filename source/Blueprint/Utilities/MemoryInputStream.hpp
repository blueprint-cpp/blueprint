#pragma once

namespace blueprint
{
    class MemoryInputStream : public std::istream
    {
    public:
        MemoryInputStream(const uint8_t* data, size_t length)
            : std::istream(&buffer_)
            , buffer_(data, length)
        {
            // reset the buffer after it has been properly constructed
            rdbuf(&buffer_);
        }

    private:
        class MemoryBuffer : public std::basic_streambuf<char>
        {
        public:
            MemoryBuffer(const uint8_t* data, size_t length)
            {
                setg((char*)data, (char*)data, (char*)data + length);
            }
        };

        MemoryBuffer buffer_;
    };
}
