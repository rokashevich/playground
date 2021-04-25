import React from 'react'
import { connect } from 'react-redux'
import Profile from './Profile'
import { getUserProfile } from '../../redux/profile-reducer'
import { withRouter } from 'react-router'
import { withAuthRedirect } from '../../hoc/withAuthRedirect'

class ProfileContainer extends React.Component {
  componentDidMount() {
    let userId = this.props.match.params.userId
    if (!userId) userId = 2
    this.props.getUserProfile(userId)
  }
  render() {
    return (
      <div>
        <Profile {...this.props} />
      </div>
    )
  }
}

let AuthRedirectComponent = withAuthRedirect(ProfileContainer)

let mapStateToProps = state => ({
  profile: state.profilePage.profile
})

// Закидывает данные из урла: match, location, history, ...
let withUrlDataContainerComponent = withRouter(AuthRedirectComponent)

export default connect(mapStateToProps, { getUserProfile })(
  withUrlDataContainerComponent
)
