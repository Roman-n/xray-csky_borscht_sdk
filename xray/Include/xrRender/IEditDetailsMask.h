#pragma once

//Режимы редактирования маски
enum class MaskEditModes {
    None = 0, // Не изменять маску
    FillByCamera, // Показывать траву в местах пролета камеры
    ClearByCamera, // Не показывать траву в местах пролета камеры
};

struct IEditDetailsMask {
    virtual ~IEditDetailsMask() = default;

    virtual bool useMask() const = 0;
    virtual void setUseMask(bool useMask) = 0;
    virtual MaskEditModes mode() const = 0;
    virtual void setMode(MaskEditModes mode) = 0;
    virtual bool changed() = 0;
    virtual void save() = 0;
};

#define IMPLEMENT_IEDIT_DETAILS_MASK                                                                                   \
    IEditDetailsMask* editDetailsMask() override { return this; }                                                      \
    bool useMask() const override { return Details->useMask(); }                                                       \
    void setUseMask(bool useMask) override { Details->setUseMask(useMask); }                                           \
    MaskEditModes mode() const override { return Details->maskEditMode(); }                                            \
    void setMode(MaskEditModes mode) override { Details->setMaskEditMode(mode); }                                      \
    bool changed() override { return Details->maskChanged(); }                                                         \
    void save() override { Details->saveMask(); }