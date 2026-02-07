import Slider from '@react-native-community/slider';
import { useState } from 'react';
import { Text, View } from "react-native";
import { Fonts } from '../constants/Fonts';
import Separator from './Separator';

function BottomSheetBrightness() {
    const [brightness, setBrightness] = useState<number>()
    const [speed, setSpeed] = useState<number>()

    return (
        <View style={{flex:1, alignItems:"flex-start", justifyContent:"center"}}>
            <Text style={{fontFamily: Fonts.mediumText, fontSize: 20}}>Jas</Text>
            <Text style={{fontFamily: Fonts.semiboldText, fontSize: 30}}>{brightness}</Text>
            <Slider
                style={{width: "70%", height: 60, alignSelf:"center", transform:[{scale: 1.5}], margin: 20}}
                minimumValue={0}
                maximumValue={256}
                onValueChange={(brightness) => setBrightness(brightness)}
            />
            <Separator />
            <Text style={{fontFamily: Fonts.mediumText, fontSize: 20}}>Rychlost</Text>
            <Text style={{fontFamily: Fonts.semiboldText, fontSize: 30}}>{speed}</Text>
            <Slider
                style={{width: "70%", height: 60, alignSelf:"center", transform:[{scale: 1.5}], margin: 20}}
                minimumValue={0}
                maximumValue={1000}
                onValueChange={(speed) => setSpeed(Math.floor(speed))}
            />
        </View>
    )
}

export default BottomSheetBrightness