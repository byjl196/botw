#pragma once

class hkBaseObject {
public:
    virtual ~hkBaseObject() = default;
    virtual void __first_virtual_table_function__() {}  // NOLINT(bugprone-reserved-identifier)
};
