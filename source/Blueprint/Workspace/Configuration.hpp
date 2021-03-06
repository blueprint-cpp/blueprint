#pragma once

namespace blueprint
{
    class Configuration
    {
    public:
        void SetName(const std::string& name);
        const std::string& GetName() const;

        void SetPrecompiledSource(const std::string& precompiledSource);
        const std::string& GetPrecompiledSource() const;

        void SetPrecompiledHeader(const std::string& precompiledHeader);
        const std::string& GetPrecompiledHeader() const;

        bool HasPrecompiledHeader() const;

    public:
        using StringArray = std::vector<std::string>;

        void AddDefine(const std::string& define);
        const StringArray& GetDefines() const;

        void AddInclude(const std::string& include);
        const StringArray& GetIncludes() const;

    private:
        std::string name_;

        StringArray defines_;
        StringArray includes_;

        std::string precompiledHeader_;
        std::string precompiledSource_;
    };
}
