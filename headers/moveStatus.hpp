#pragma once

namespace path_finding
{
    /// <summary>
    /// Move status enumerator to identify the units movement status
    /// </summary>
    enum class move_status
    {
        at_target,
        no_path,
        blocked,
        moved
    };
}
