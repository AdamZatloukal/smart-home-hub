import { Pressable, Text } from "react-native";
import { Colors } from "../constants/Colors";
import { styles } from "../styles/RoomButton";

type RoomButtonProps = {
    roomName: string
}

function RoomButton({ roomName }: RoomButtonProps) {
    return (
        <Pressable
            style={({ pressed }) => [
                styles.roomSelectButton,
                {
                    backgroundColor: pressed ? Colors.applianceCardPressed : "transparent"
                }
            ]}
        >
            <Text style={styles.roomSelectText}>{roomName}</Text>
        </Pressable>
    )
}

export default RoomButton;