import { View } from "react-native";
import { Colors } from "../constants/Colors";

function Separator() {
    return (
        <View style={{ width: "100%", borderColor: Colors.bottomSheetLine, borderTopWidth: 1, margin: 30, alignSelf: "center" }} />
    );
}

export default Separator;