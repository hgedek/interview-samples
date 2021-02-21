function parseInt(value) {
    value = value.trim();
    if ( value.length === 0) return NaN;

    // if alpha or alphanumeric return NaN
    if (isNaN(value)) return NaN;

    var result = 0;

    if (value.startsWith("0x")) {
        var sub = value.substr(2, value.length - 2);
        for (let i = 0; i < sub.length; i++)
            result += sub[i] * Math.pow(16, sub.length - i - 1);
    } else {
        for (let i = 0; i < value.length; i++)
            result += value[i] * Math.pow(10, value.length - i - 1);
    }

    return result;

    // Sorry I didnt understand this !
    // Only the first number in the string is returned. If the first character, or group of
    // characters, cannot be converted to a number returns NaN.
}
